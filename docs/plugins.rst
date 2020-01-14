Plugins
=======

The library supports I/O plugins in order to enable RPC communication over a
range of interfaces. Currently, the following plugins are implemented.

.. list-table:: Plugins.
   :header-rows: 1

   * - name
     - description
     - status
   * - ``HardwareSerialIO``
     - The standard Arduino serial interface.
     - working
   * - ``SoftwareSerialIO``
     - Arduino serial interface using arbitrary pins.
     - untested
   * - ``WireIO``
     -  I2C / TWI interface.
     - untested

All plugins have at least the following methods.

.. list-table:: Methods.
   :header-rows: 1

   * - name
     - description
     - parameters
   * -
     - Constructor.
     - none
   * - ``begin()``
     - Initialisation function.
     - depends on plugin
   * - ``available()``
     - Number of bytes available for reading.
     - none
   * - ``read()``
     - Read a number of bytes into a buffer.
     - ``byte* data``, ``size_t size``
   * - ``write()``
     - Write a number of bytes from a buffer.
     - ``byte* data``, ``size_t size``

Usually, the I/O plugin is declared as a global object instance in the sketch
and the ``begin()`` method is invoked from the ``setup()`` function.

The constructor and the methods ``available()``, ``read()`` and ``write()`` are
fixed for all plugins. The ``begin()`` function may differ between plugins.


``HardwareSerialIO``
--------------------

The Arduino hardware has built-in support for serial communication on pins 0
and 1 (which also goes to the computer via the USB connection). The
``HardwareSerialIO`` plugin is a wrapper for the Serial_ library, which allows
communication with the hardware serial interface.

The ``begin()`` method of this plugin takes a class instance of type
``HardwareSerial`` as parameter.

Example
^^^^^^^

A typical use of the ``HardwareSerialIO`` plugin is as follows.

.. code:: cpp

    HardwareSerialIO io;

    void setup(void) {
      Serial.begin(9600);
      io.begin(Serial);
    }


``SoftwareSerialIO``
--------------------

The SoftwareSerial_ library has been developed to allow serial communication on
other digital pins of the Arduino. The ``SoftwareSerialIO`` plugin is a wrapper
for this library.

The ``begin()`` method of this plugin takes a class instance of type
``SoftwareSerial`` as parameter.

Example
^^^^^^^

A typical use of the ``SoftwareSerialIO`` plugin is as follows.

.. code:: cpp

    SoftwareSerial ss(2, 3);
    SoftwareSerialIO io;

    void setup(void) {
      ss.begin(9600);
      io.begin(ss);
    }


``WireIO``
----------

The Wire_ library allows for communication using the I2C / TWI interface. The
``WireIO`` plugin is a wrapper for this library.

The ``begin()`` method of this plugin takes a class instance of type
``TwoWire`` as parameter.

Example
^^^^^^^

A typical use of the ``WireIO`` plugin is as follows.

.. code:: cpp

    WireIO io;

    void setup(void) {
      io.begin(Wire);
    }


Multiple I/O interfaces
-----------------------

It is possible to use multiple I/O interfaces at the same time. This can be
done by either serving a different set of methods on each interface or by
serving the same set of methods on multiple interfaces.

To serve different methods on each interface, the ``interface()`` function is
simply used multiple times.

Example
^^^^^^^

Suppose we have set up two I/O interfaces named ``ioHardware`` and
``ioSoftware``, we serve different methods on each of the interfaces as
follows.

.. code:: cpp

    void loop(void) {
      interface(
        ioHardware,
        inc, F("inc: Increment a value. @a: Value. @return: a + 1."));
      interface(
        ioSoftware,
        setLed, F("set_led: Set LED brightness. @brightness: Brightness."));
    }

Alternatively, it is possible to serve the same set of methods on multiple
interfaces. This can be done by passing a Tuple of pointers to the interfaces
as the first parameter of the ``interface()`` function.

Example
^^^^^^^

Suppose we have set up two I/O interfaces named ``ioHardware`` and
``ioSoftware``, we serve the same methods on both interfaces by grouping
pointers to these interfaces with the ``pack()`` function as follows.

.. code:: cpp

    void loop(void) {
      interface(
        pack(&ioHardware, &ioSoftware),
        inc, F("inc: Increment a value. @a: Value. @return: a + 1."));
    }

Finally, it is possible to combine both of the strategies described above.


.. _Serial: https://www.arduino.cc/en/Reference/Serial
.. _SoftwareSerial: https://www.arduino.cc/en/Reference/SoftwareSerial
.. _Wire: https://www.arduino.cc/en/Reference/Wire
