from serial import Serial
from struct import calcsize, pack, unpack
from time import sleep


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

        # Any invalid method index results in an interface description.
        self._connection.write(pack('B', 0xff))
        for index in range(ord(self._connection.read(1))):
            m_type, m_name, m_args = self._connection.readline(
                ).strip().split(' ', 2)
            self.methods[m_name] = {
                'index': index, 'type': m_type, 'args': m_args.split(', ')}

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
        self._connection.write(pack('B', method['index']))
        if m_args and _types[m_args[0]][0] != 'x':
            for index, a_type in enumerate(m_args):
                fmt, cast = _types[a_type]
                self._connection.write(pack(fmt, cast(args[index])))

        fmt = _types[method['type']][0]
        if fmt != 'x':
            return unpack(fmt, self._connection.read(calcsize(fmt)))[0]

        return None
