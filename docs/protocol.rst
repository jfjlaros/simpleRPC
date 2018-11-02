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

Method discovery is initiated by the host by writing one byte with the value
``0xff`` to the serial device.

The device will respond with a list of method descriptions delimited by an end
of line signature (``0x0d0a``). The list is terminated by an additional end of
line signature.

Each method description consists of a C-style function signature enclosed in
brackets followed by a documentation string. The format of the documentation
string is described in the :doc:`usage_device` section.


Remote procedure call
---------------------

A remote procedure call is initiated by the host by writing one byte to the
serial device of which the value maps to one of the exported methods (i.e., 0
maps to the first method, 1 to the second, etc.). If this method takes any
parameters, their values are written to the serial device. After the parameter
values have been received, the device executes the method and writes the return
value of the method (if any) back to the serial device.

All types are native C types (``int``, ``float``, ``double``, etc.). All values
are little-endian. The sizes of the different types can be found in the
Arduino_ documentation. The host is responsible for packing and unpacking of
the variables. An example conversion table named ``_types`` can be found In the
file simple_rpc.py_.


.. _Arduino: https://www.arduino.cc/reference/en/#variables
.. _simple_rpc.py: https://github.com/jfjlaros/simpleRPC/blob/master/simple_rpc/simple_rpc.py
