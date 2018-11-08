from serial import Serial
from struct import calcsize, pack, unpack
from time import sleep
from types import MethodType


_version = 2

_list_req = 0xff
_end_of_line = '\n'


def _cast(c_type):
    """Select the appropriate casting function given a C type.

    :arg str c_type: C type.

    :returns obj: Casting function.
    """
    if c_type[0] == 'c':
        return str
    if c_type[-1] in ['f', 'd']:
        return float
    return int


def type_name(c_type):
    return _cast(c_type).__name__


#def _parse_doc(doc):
#    """Parse the method documentation string.
#
#    :arg str doc: Method documentation string.
#
#    :returns dict: Method documentation.
#    """
#    # TODO: Allow for missing or malformed documentation strings.
#    doc_parts = doc.split(' @')
#
#    documentation = {
#        'name': doc_parts[0],
#        'parameters': [],
#        'type': ''}
#
#    for item in doc_parts[1:]:
#        doc_type, doc_text = item.split(':', 1)
#        if doc_type == 'P':
#            documentation['parameters'].append(doc_text)
#        if doc_type == 'R':
#            documentation['type'] = doc_text
#
#    return documentation


def _parse_signature(index, signature):
    method = {
        'doc': '',
        'index': index, # FIXME, not sure this should be here.
        'name': 'method{}'.format(index),
        'parameters': [],
        'return': {'doc': ''}}

    method['return']['type'], parameters = signature.split(':')

    for i, type_ in enumerate(parameters.split()):
        method['parameters'].append({
            'doc': '',
            'name': 'arg{}'.format(i),
            'type': type_})

    return method


def _parse_line(index, line):
    """Parse a method definition line.

    :arg int index: Line number.
    :arg str line: Method definition.

    :returns dict: Method dictionary.
    """
    #print(line)
    signature, description = line.strip(_end_of_line).split('; ', 1)

    return _parse_signature(index, signature)
    #r_type, tail = signature.split(':')
    #p_types = tail.split()
    #name, doc = description.split(': ', 1)

    #return {
    #    'index': index,
    #    'type': r_type,
    #    'name': name,
    #    'parameters': p_types,
    #    'doc': _parse_doc(doc)}


def _make_docstring(method):
    """Make a docstring for a function.

    :arg dict method: Method dictionary.

    :returns str: Function docstring.
    """
    help_text = '{}'.format(method['name'])

    if method['parameters']:
        help_text += '\n'
        for parameter in method['parameters']:
            help_text += '\n:{}: {}'.format(
                type_name(parameter['type']), parameter['doc'])

    if method['return']['type']:
        help_text += '\n\n:returns {}: {}'.format(
            type_name(method['return']['type']), method['return']['doc'])

    return help_text


class Interface(object):
    def __init__(self, device, baudrate=9600):
        """Initialise the class.

        :arg str device: Serial device name.
        :arg int baudrate: Baud rate.
        """
        self._connection = Serial(device, baudrate)
        sleep(1)

        self.methods = dict(map(lambda x: (x['name'], x), self._get_methods()))
        for method in self.methods.values():
            setattr(self, method['name'], MethodType(self._call(method), self))

        #device_version = self.call_method('version')
        #if device_version != _version:
        #    raise ValueError(
        #        'version mismatch (device: {}, client: {})'.format(
        #            device_version, _version))

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
        self._connection.write(
            pack(param_type, _cast(param_type)(param_value)))

    def _read_value(self, return_type):
        """Read a return value from a remote procedure call.

        :arg str return_type: Return type.

        :returns any: Return value.
        """
        return unpack(
            return_type, self._connection.read(calcsize(return_type)))[0]

    def _get_methods(self):
        """Get a list of remote procedure call methods.

        :returns dict: Method dictionary.
        """
        self._select(_list_req)

        methods = []
        index = 0
        while True:
            line = self._connection.readline().decode('utf-8')
            if line == _end_of_line:
                break
            methods.append(_parse_line(index, line))
            index += 1

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
            #for param_type, param_value in zip(method['parameters'], args):
            for index, parameter in enumerate(method['parameters']):
                self._write_parameter(parameter['type'], args[index])

        # Read return value (if any).
        if method['return']['type']:
            return self._read_value(method['return']['type'])
        return None
