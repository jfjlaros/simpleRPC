Plugins
=======

The library supports I/O plugins in order to enable RPC communication over a
range of interfaces. Currently, the following plugins are implemented.

.. list-table:: Plugins.
   :header-rows: 1

   * - name
     - description
     - status
   * - ``Serial``
     - The standard Arduino Serial_ interface.
     - working
   * - ``SoftwareSerial``
     - The Arduino SoftwareSerial_ interface.
     - untested
   * - ``HalfDuplexStream``
     - RS485 serial interface.
     - working
   * - ``EthernetClient``
     - Arduino Ethernet_ interface.
     - untested
   * - ``WiFiClient``
     - Arduino WiFi_ interface.
     - working
   * - ``Wire``
     - I2C / TWI Wire_ interface.
     - untested

A plugin inherits from ``Stream`` and should override the following
methods.

.. list-table:: Methods.
   :header-rows: 1

   * - name
     - description
   * -
     - Constructor.
   * - ``int available()``
     - Number of bytes available for reading.
   * - ``int read()``
     - Read a single byte or ``-1`` upon error.
   * - ``int peek()``
     - Preview the next byte.
   * - ``size_t write(uint8_t)``
     - Write a single byte, return the number of bytes written.

Usually, the I/O plugin is declared as a global object instance in the sketch
and initialized in the ``setup()`` function. See the RS485_ sketch for an
example that uses a custom I/O plugin.


Multiple I/O interfaces
-----------------------

It is possible to use multiple I/O interfaces at the same time. This can be
done by either serving a different set of methods on each interface or by
serving the same set of methods on multiple interfaces.

To serve different methods on each interface, the ``interface()`` function is
simply used multiple times.

Example
^^^^^^^

Suppose we have set up two I/O interfaces named ``Serial`` and
``SerialUSB``, we serve different methods on each of the interfaces as
follows.

.. code-block:: cpp

    void loop(void) {
      interface(
        Serial,
        inc, F("inc: Increment a value. @a: Value. @return: a + 1."));
      interface(
        SerialUSB,
        setLed, F("set_led: Set LED brightness. @brightness: Brightness."));
    }

Alternatively, it is possible to serve the same set of methods on multiple
interfaces. This can be done by passing a Tuple of pointers to the interfaces
as the first parameter of the ``interface()`` function.

Example
^^^^^^^

Suppose we have set up two I/O interfaces named ``Serial`` and
``SerialUSB``, we serve the same methods on both interfaces by grouping
pointers to these interfaces with the ``pack()`` function as follows.

.. code-block:: cpp

    void loop(void) {
      interface(
        pack(&Serial, &SerialUSB),
        inc, F("inc: Increment a value. @a: Value. @return: a + 1."));
    }

Finally, it is possible to combine both of the strategies described above.


.. _Ethernet: https://www.arduino.cc/en/Reference/Ethernet
.. _RS485: https://github.com/jfjlaros/simpleRPC/blob/master/examples/rs485/rs485.ino
.. _Serial: https://www.arduino.cc/en/Reference/Serial
.. _SoftwareSerial: https://www.arduino.cc/en/Reference/SoftwareSerial
.. _WiFi: https://www.arduino.cc/en/Reference/WiFi101
.. _Wire: https://www.arduino.cc/en/Reference/Wire
