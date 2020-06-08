Introduction
============

A remote procedure call to an Arduino device is a common way to read sensor
values or to send control signals. This library provides a simple way to export
any Arduino function, including API documentation.


Motivation
----------

Suppose we have an number of functions that we want to export as remote
procedure calls.

.. code-block:: cpp

    int testInt(void) {
      return 1;
    }

    float testFloat(void) {
      return 1.6180339887;
    }

    int add(int a, int b) {
      return a + b;
    }

A common way of making functions available is to map each of the functions to
an unique value. The Arduino reads one byte from an I/O device and it uses this
to select the appropriated function.

If a function takes parameters, their values need to be read from the I/O
device before calling the function. Any return value needs to be written to the
I/O device after calling the function.

A typical implementation of such an approach is shown below.

.. code-block:: cpp

    void loop(void) {
      int iValue, iParamA, iParamB;
      float fValue;

      if (Serial.available()) {
        switch (Serial.read()) {
          case 0x00:
            iValue = testInt();
            Serial.write((byte*)&iValue, 2);
            break;
          case 0x01:
            fValue = testFloat();
            Serial.write((byte*)&fValue, 4);
            break;
          case 0x02:
            Serial.readBytes((char*)&iParamA, 2);
            Serial.readBytes((char*)&iParamB, 2);
            iValue = add(iParamA, iParamB);
            Serial.write((byte*)&iValue, 2);
            break;
        }
      }
    }

In this implementation, the methods ``Serial.write()`` and
``Serial.readBytes()`` are used to encode and decode values.

On the host, the parameter values need to be packed before sending them to the
Arduino, Any return value needs to be unpacked. In the following example, we
assume that a serial connection is made using the pySerial_ library. The
functions ``pack`` and ``unpack`` are provided by the struct_ library.

.. code-block:: python

    # Call the testInt() function.
    connection.write(pack('B', 0x00))
    print(unpack('<h', connection.read(2))[0])

    # Call the testFloat() function.
    connection.write(pack('B', 0x01))
    print(unpack('<f', connection.read(4))[0])

    # Call the add() function.
    connection.write(pack('B', 0x02))
    connection.write(pack('<h', 1))
    connection.write(pack('<h', 2))
    print(unpack('<h', connection.read(2))[0])

An implementation like the one described above uses very little bandwidth and
does not require any heavy external libraries on the Arduino. The downsides of
such an approach are clear from the example:

- Quite a bit of boilerplate code is needed.
- Changes have to be made on both the device and the host, keeping the
  implementations in sync may become difficult.
- A lot of low-level knowledge of the device methods and their types is
  required.

This is where the simpleRPC library comes in, like the implementation above, it
only communicates values but has none of the downsides of an *ad hoc* protocol.


.. _struct: https://docs.python.org/2/library/struct.html
.. _pySerial: https://pythonhosted.org/pyserial/
