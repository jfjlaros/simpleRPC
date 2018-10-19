from serial import Serial
from struct import calcsize, pack, unpack
from time import sleep
from types import MethodType


_types = {
    'void': ['x', None],
    'char': ['c', str],
    'signed char': ['b', int],
    'unsigned char': ['B', int],
    'byte': ['B', str],
    'bool': ['?', bool],
    'short': ['<h', int],
    'signed short': ['<h', int],
    'unsigned short': ['<H', int],
    'int': ['<h', int],
    'signed int': ['<h', int],
    'unsigned int': ['<H', int],
    'long': ['<l', int],
    'signed long': ['<l', int],
    'unsigned long': ['<L', int],
    'float': ['<f', float],
    'double': ['<f', float]}


def _parse_doc(doc):
    """Parse the method documentation string.

    :arg str doc: Method documentation string.

    :returns dict: Method documentation.
    """
    doc_parts = doc.split(' @')

    documentation = {
        'name': doc_parts[0],
        'parameters': [],
        'type': ''}

    for item in doc_parts[1:]:
        doc_type, doc_text = item.split(':', 1)
        if doc_type == 'P':
            documentation['parameters'].append(doc_text)
        if doc_type == 'R':
            documentation['type'] = doc_text

    return documentation


def _strip_void(obj):
    """Remove void types.

    :arg any obj: Type or list of types.

    :returns any: Type or list of types without void types.
    """
    if obj == 'void':
        return ''
    if obj == ['void']:
        return []
    return obj


def _parse_line(index, line):
    """Parse a method definition line.

    :arg int index: Line number.
    :arg str line: Method definition.

    :returns dict: Method dictionary.
    """
    line_parts = line.strip().split(';', 3)

    return {
        'index': index,
        'type': _strip_void(line_parts[0]),
        'name': line_parts[1],
        'parameters': _strip_void(line_parts[2].split(', ')),
        'doc': _parse_doc(line_parts[3])}


def _make_docstring(method):
    """Make a docstring for a function.

    :arg dict method: Method dictionary.

    :returns str: Function docstring.
    """
    help_text = '{}'.format(method['doc']['name'])

    if method['parameters']:
        help_text += '\n'
        for index, parameter in enumerate(method['parameters']):
            help_text += '\n:arg {}: {}'.format(
                parameter, method['doc']['parameters'][index])

    if method['type']:
        help_text += '\n\n:returns {}: {}'.format(
            method['type'], method['doc']['type'])

    return help_text


class Interface(object):
    def __init__(self, device):
        """Initialise the class.

        :arg str device: Serial device name.
        """
        self._connection = Serial(device)
        sleep(1)

        self.methods = dict(map(lambda x: (x['name'], x), self._get_methods()))
        for method in self.methods.values():
            setattr(self, method['name'], MethodType(self._call(method), self))

    def _select(self, index):
        """Initiate a remote procedure call, select the method.

        :arg int index: Method index.
        """
        self._connection.write(pack('B', index))

    def _write_parameter(self, param_type, param_value):
        """Provide parameters for a remote procedure call.

        :arg str param_type: Type of the parameter.
        :arg str param_value: Value of the parameter.
        """
        fmt, cast = _types[param_type]
        self._connection.write(pack(fmt, cast(param_value)))

    def _read_value(self, return_type):
        """Read a return value from a remote procedure call.

        :arg str return_type: Return type.

        :returns any: Return value.
        """
        fmt = _types[return_type][0]

        return unpack(fmt, self._connection.read(calcsize(fmt)))[0]

    def _get_methods(self):
        """Get a list of remote procedure call methods.

        :returns dict: Method dictionary.
        """
        self._select(0xff)
        number_of_methods = self._read_value('unsigned char')

        methods = []
        for index in range(number_of_methods):
            methods.append(_parse_line(
                index, self._connection.readline().decode('utf-8')))

        return methods

    def _call(self, method, *args):
        """Make a member function for a method.

        :arg dict method: Method dictionary.
        :arg any *args: Parameters for the method.

        :returns function: New member function.
        """
        def call(self, *args):
            return self.call_method(method['name'], *args)
        call.__name__ = method['name']
        call.__doc__ = _make_docstring(method)

        return call

    def call_method(self, name, *args):
        """Execute a method.

        :arg str name: Method name.
        :arg list *args: Method parameters.

        :returns any: Return value of the method.
        """
        if name not in self.methods:
            raise ValueError('invalid method name: {}'.format(name))
        method = self.methods[name]

        parameters = method['parameters']
        if len(args) != len(parameters):
            raise ValueError(
                'got {} parameters for method {}, expected {}'.format(
                    len(args), name, len(parameters)))

        # Call the method.
        self._select(method['index'])

        # Provide parameters (if any).
        if method['parameters']:
            for param_type, param_value in zip(method['parameters'], args):
                self._write_parameter(param_type, param_value)

        # Read return value (if any).
        if method['type']:
            return self._read_value(method['type'])
        return None
