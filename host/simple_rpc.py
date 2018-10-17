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


def _make_help(method):
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


def _parse_doc(doc):
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
    if obj == 'void':
        return ''
    if obj == ['void']:
        return []
    return obj


def _parse_line(index, line):
    line_parts = line.strip().split(';', 3)

    return {
        'index': index,
        'type': _strip_void(line_parts[0]),
        'name': line_parts[1],
        'parameters': _strip_void(line_parts[2].split(', ')),
        'doc': _parse_doc(line_parts[3])}


class Interface(object):
    def __init__(self, device):
        """Initialise the class.

        :arg str device: Serial device name.
        """
        self._connection = Serial(device)
        sleep(1)

        methods = self._get_methods()
        self._methods = dict(map(lambda x: (x['name'], x), methods))

        for method in methods:
            setattr(self, method['name'], MethodType(self._wrap(method), self))

    def _select(self, index):
        self._connection.write(pack('B', index))

    def _write_parameter(self, param_type, param_value):
        fmt, cast = _types[param_type]
        self._connection.write(pack(fmt, cast(param_value)))

    def _read_value(self, return_type):
        fmt = _types[return_type][0]
        return unpack(fmt, self._connection.read(calcsize(fmt)))[0]

    def _get_methods(self):
        self._select(0xff)
        number_of_methods = ord(self._connection.read(1))

        methods = []
        for index in range(number_of_methods):
            methods.append(_parse_line(index, self._connection.readline()))

        return methods

    def _wrap(self, method, *args):
        def wrap(self, *args):
            return self.call_method(method['name'], *args)
        wrap.__doc__ = _make_help(method)

        return wrap

    def call_method(self, name, *args):
        """Execute a method.

        :arg str name: Method name.
        :arg list *args: Method parameters.

        :returns any: Return value of the method.
        """
        if name not in self._methods:
            raise ValueError('invalid method name: {}'.format(name))
        method = self._methods[name]

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
