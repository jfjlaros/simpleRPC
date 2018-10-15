from serial import Serial
from struct import calcsize, pack, unpack
from sys import stdout
from time import sleep


_types = {
    'void': 'x',
    'char': 'c',
    'signed char': 'b',
    'unsigned char': 'B',
    'byte': 'B',
    'bool': '?',
    'short': '<h',
    'signed short': '<h',
    'unsigned short': '<H',
    'int': '<h',
    'signed int': '<h',
    'unsigned int': '<H',
    'long': '<l',
    'signed long': '<l',
    'unsigned long': '<L',
    'float': '<f',
    'double': '<f'}


class Interface(object):
    def __init__(self, device, handle=stdout):
        self._connection = Serial(device)
        self._handle = handle
        self._methods = {}

        sleep(1)
        self._build()

    def _build(self):
        self._connection.write(pack('B', 0xff))

        for index in range(ord(self._connection.read(1))):
            m_type, m_name, m_args = self._connection.readline(
                ).strip().split(' ', 2)
            self._methods[m_name] = {
                'index': index,
                'type': _types[m_type],
                'args': map(lambda x: _types[x], m_args.split(', '))}

    def methods(self):
        for name in self._methods:
            method = self._methods[name]
            self._handle.write('0x{:02x}: {} {} {}\n'.format(
                method['index'], method['type'], name, method['args']))

    def cmd(self, name, *args):
        method = self._methods[name]

        self._connection.write(pack('B', method['index']))
        if method['args'] and method['args'][0] != 'x':
            for index, m_arg in enumerate(method['args']):
                self._connection.write(pack(m_arg, args[index]))

        if method['type'] != 'x':
            return unpack(
                method['type'],
                self._connection.read(calcsize(method['type'])))[0]
        return None


def main():
    interface = Interface('/dev/ttyACM0')

    interface.methods()

    while True:
        print interface.cmd('bla')
        print interface.cmd('add', 123, 456)
        interface.cmd('setLed', 255)
        sleep(1)
        interface.cmd('setLed', 40)
        sleep(1)


if __name__ == '__main__':
    main()
