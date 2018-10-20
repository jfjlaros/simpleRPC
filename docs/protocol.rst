Protocol
========

In this section we describe the serial protocol.

Every exported method defined in ``methods.h`` (See `Device library`_) is
assigned a number between 0 and 254 in order of appearance. The number 0 maps
to the first method, the number 1 maps to the second method, etc.

There are two types of calls to the device: the method discovery call and a
remote procedure call. In both cases, the communication is initiated by the
host by writing one byte to the serial device. If this byte maps to an exported
method, a remote procedure call is initiated, the method discovery procedure is
executed otherwise.


Method discovery
----------------

Method discovery is initiated by the host by writing one byte to the serial
device. The value of this byte should not map to an exported method. The
preferred value is ``0xff``.

The device will respond with one byte containing the number of methods followed
by a list of method descriptions delimited by an end of line signature
(``0x0d0a``).

+---------+-------------+----------------------------------------+
| field   | delimiter   | description                            |
+=========+=============+========================================+
| 0       | ``;``       | Return type.                           |
+---------+-------------+----------------------------------------+
| 2       | ``;``       | Method name.                           |
+---------+-------------+----------------------------------------+
| 3       | ``;``       | List of ``, `` separated parameters.   |
+---------+-------------+----------------------------------------+
| 4       |             | Documentation string.                  |
+---------+-------------+----------------------------------------+

The format of the documentation string is described in Table
`Documentation string.`_.

Remote procedure call
---------------------
