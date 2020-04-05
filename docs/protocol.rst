Protocol
========

In this section we describe the RPC protocol.

Every exported method defined using the ``interface()`` function (see the
:doc:`usage` section) is assigned a number between 0 and 254 in order of
appearance. The number 0 maps to the first method, the number 1 maps to the
second method, etc.

There are two types of calls to the device: the method discovery call and a
remote procedure call. In both cases, communication is initiated by the host by
writing one byte to the I/O device.


.. _method_discovery:

Method discovery
----------------

Method discovery is initiated by the host by writing one byte with value
``0xff`` to the I/O device.

The device will respond with a header and a list of method descriptions
delimited by an end of string signature (``\0``). The list is terminated by an
additional end of string signature. The header format is given in the following
table.

.. list-table:: Header format.
   :header-rows: 1

   * - size
     - delimiter
     - value
     - description
   * -
     - ``\0``
     - ``simpleRPC``
     - Protocol identifier.
   * - 3
     -
     - ``\3\0\0`` (example)
     - Protocol version (major, minor, patch).
   * - 1
     -
     - ``<`` or ``>``
     - Endianness, ``<`` for little-endian, ``>`` for big-endian.
   * - 1
     -
     - ``H`` (example)
     - Type of ``size_t``, needed for indexing vectors.

Each method description consists of a struct_ formatted function signature and
a documentation string separated by a ``;``. The function signature starts with
a struct formatted return type (if any), followed by a ``:`` and a space
delimited list of struct formatted parameter types. The format of the
documentation string is described in the :doc:`usage` section.

For our example, the response for the method discovery request will look as
follows.

::

    h: h;inc: Increment a value. @a: Value. @return: a + 1.\0
    : B;set_led: Set LED brightness. @brightness: Brightness.\0
    \0

For more complex objects, like Tuples, Objects and Vectors, some more syntax is
needed to communicate their structure to the host.

A Tuple type is encoded as a compound type, e.g., ``hB`` (a 16-bit integer and
a byte). It can be recognised by the absence of a space between the type
signatures. Note that a concatenated or nested Tuple type can not be recognised
from its signature, e.g., ``hB`` concatenated with ``ff`` is indistinguishable
from ``hBff``

An Object type is encoded as a compound type like a Tuple, but its type
signature is enclosed in parentheses ``(`` and ``)``, which makes it possible
to communicate its structure to the host, e.g., the concatenation of ``(hB)``
and ``(ff)`` is ``(hB)(ff)`` and the type signature of a nested Object may look
like this ``((hB)(ff))``.

A Vector type signature is enclosed in brackets ``[`` and ``]``. So a vector of
16-bit integers will have as type signature ``[h]``.

Finally, any arbitrary combination of Tuples, Objects and Vectors can be made,
resulting in type signatures like ``[((hB)f)]``, i.e., a Vector of Objects that
contain a Tuple of which the first element is an other Object ``(hB)`` and
the second element is a float ``f``.


Remote procedure calls
----------------------

A remote procedure call is initiated by the host by writing one byte to the
I/O device of which the value maps to one of the exported methods (i.e., 0
maps to the first method, 1 to the second, etc.). If this method takes any
parameters, their values are written to the I/O device. After the parameter
values have been received, the device executes the method and writes its return
value (if any) back to the I/O device.

All native C types (``int``, ``float``, ``double``, etc.), Tuples, Objects,
Vectors and any combination of these are currently supported. The host is
responsible for packing and unpacking of the values.


.. _struct: https://docs.python.org/3.5/library/struct.html#format-strings
