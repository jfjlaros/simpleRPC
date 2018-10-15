from serial import Serial
from struct import calcsize, pack, unpack
from sys import stdout
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
    def __init__(self, device, handle=stdout):
        self._connection = Serial(device)
        self._handle = handle
        self.methods = {}

        sleep(1)
        self._build()

    def _build(self):
        self._connection.write(pack('B', 0xff))

        for index in range(ord(self._connection.read(1))):
            m_type, m_name, m_args = self._connection.readline(
                ).strip().split(' ', 2)
            self.methods[m_name] = {
                'index': index, 'type': m_type, 'args': m_args.split(', ')}

    def cmd(self, name, *args):
        method = self.methods[name]

        self._connection.write(pack('B', method['index']))
        if method['args'] and _types[method['args'][0]][0] != 'x':
            for index, m_arg in enumerate(method['args']):
                self._connection.write(
                    pack(_types[m_arg][0],
                    _types[m_arg][1](args[index])))

        if _types[method['type']][0] != 'x':
            fmt = _types[method['type']][0]
            return unpack(fmt, self._connection.read(calcsize(fmt)))[0]

        return None
