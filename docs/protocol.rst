Protocol
========

In this section we describe the serial protocol.

Every exported method defined using the ``interface()`` function (see the
:doc:`usage_device` section) is assigned a number between 0 and 254 in order of
appearance. The number 0 maps to the first method, the number 1 maps to the
second method, etc.

There are two types of calls to the device: the method discovery call and a
remote procedure call. In both cases, communication is initiated by the host by
writing one byte to the serial device.


Method discovery
----------------

Method discovery is initiated by the host by writing one byte with value
``0xff`` to the serial device.

The device will respond with a list of method descriptions delimited by an end
of line signature (``\n``). The list is terminated by an additional end of line
signature.

Each method description consists of a struct_ formatted function signature and
a documentation string separated by a ``;``. The function signature starts with
a struct formatted return type (if any), followed by a ``:`` and a space
delimited list of struct formatted parameter types. The format of the
documentation string is described in the :doc:`usage_device` section.


Remote procedure call
---------------------

A remote procedure call is initiated by the host by writing one byte to the
serial device of which the value maps to one of the exported methods (i.e., 0
maps to the first method, 1 to the second, etc.). If this method takes any
parameters, their values are written to the serial device. After the parameter
values have been received, the device executes the method and writes the return
value of the method (if any) back to the serial device.

All native C types (``int``, ``float``, ``double``, etc.) are currently
supported.  All values are little-endian. The host is responsible for packing
and unpacking of the values.

There are currently two built-in functions.

.. list-table:: Built-in functions.
   :header-rows: 1

   * - index
     - name
     - description
     - parameters
     - returns
   * - 0
     - version
     - Protocol version.
     -
     - int: Version number.
   * - 1
     - ping
     - Echo a value.
     - int data: Value.
     - int: Value of data.


Overhead
--------

There does not seem to be any noticeable overhead of the library. We tested the
throughput by calling the ``ping()`` function repeatedly at baud rates ranging
from 600 baud to 115200 baud.

.. list-table:: Throughput statistics.
   :header-rows: 1

   * - baud rate
     - calls per second
   * - 600
     - 30
   * - 1200
     - 60
   * - 2400
     - 120
   * - 4800
     - 239
   * - 9600
     - 480
   * - 14400
     - 718
   * - 19200
     - 959
   * - 28800
     - 1447
   * - 31250
     - 1559
   * - 38400
     - 1920
   * - 57600
     - 2924
   * - 115200
     - 5838

The number of calls per second scales linearly with the baud rate, even at the
highest speed, there is no measurable overhead.


.. _struct: https://docs.python.org/2/library/struct.html#format-characters
