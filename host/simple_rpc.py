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


class Interface(object):
    def __init__(self, device):
        """Initialise the class.

        :arg str device: Serial device name.
        """
        self._connection = Serial(device)
        self.methods = {}
        sleep(1)

        # Any invalid method index returns an interface description.
        self._connection.write(pack('B', 0xff))
        for index in range(ord(self._connection.read(1))):
            m_type, m_name, m_args = self._connection.readline(
                ).strip().split(' ', 2)
            self.methods[m_name] = {
                'index': index, 'type': m_type, 'args': m_args.split(', ')}

        for name in self.methods:
            setattr(self, name, MethodType(self._wrap(name), self))

    def _wrap(self, name, *args):
        def wrap(self, *args):
            return self.cmd(name, *args)
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
        self._connection.write(pack('B', method['index']))

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
