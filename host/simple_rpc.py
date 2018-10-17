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

    if method['parameters'][0] != 'void':
        help_text += '\n'
        for index, parameter in enumerate(method['parameters']):
            help_text += '\n:arg {}: {}'.format(
                parameter, method['doc']['parameters'][index])

    if method['type'] != 'void':
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


def _parse_line(index, line):
    line_parts = line.strip().split(';', 3)

    return {
        'index': index,
        'type': line_parts[0],
        'name': line_parts[1],
        'parameters': line_parts[2].split(', '),
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

        # TODO: rewrite
        self.methods = {}
        # Any invalid method index returns an interface description.
        self._connection.write(pack('B', 0xff))
        for index in range(ord(self._connection.read(1))):
            m_type, m_name, m_args, m_doc = self._connection.readline(
                ).strip().split(';', 3)
            self.methods[m_name] = {
                'index': index, 'type': m_type, 'args': m_args.split(', ')}
        # TODO: /rewrite

    def _select(self, index):
        self._connection.write(pack('B', index))

    def _get_methods(self):
        self._select(0xff)
        number_of_methods = ord(self._connection.read(1))

        methods = []
        for index in range(number_of_methods):
            methods.append(_parse_line(index, self._connection.readline()))

        return methods

    def _wrap(self, method, *args):
        def wrap(self, *args):
            return self.cmd(method['name'], *args)
        wrap.__doc__ = _make_help(method)

        return wrap

    def cmd(self, name, *args):
        """Execute a method.

        :arg str name: Method name.
        :arg list *args: Method parameters.

        :returns any: Return value of the method.
        """
        if name not in self.methods:
            raise ValueError('invalid method name: {}'.format(name))
        method = self.methods[name]

        m_args = method['args']
        if m_args[0] == 'void':
            m_args = []
        if len(args) != len(m_args):
            raise ValueError(
                'got {} parameters for method {}, expected {}'.format(
                    len(args), name, len(m_args)))

        # Call the method.
        self._select(method['index'])

        # Provide parameters (if any).
        if m_args:
            for index, a_type in enumerate(m_args):
                fmt, cast = _types[a_type]
                self._connection.write(pack(fmt, cast(args[index])))

        # Read return value (if any).
        if method['type'] != 'void':
            fmt = _types[method['type']][0]
            return unpack(fmt, self._connection.read(calcsize(fmt)))[0]
        return None
