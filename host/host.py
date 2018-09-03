#!/usr/bin/env python
import serial


def main():
    connection = serial.Serial('/dev/ttyACM0')


if __name__ == '__main__':
    main()
