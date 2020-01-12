Plugins
=======

The library supports I/O plugins in order to enable RPC communication over a
range of interfaces, 
Currently, the folowing plugins are implemented.

.. list-table:: Plugins.
   :header-rows: 1

   * - name
     - description
   * - HardwareSerialIO
     - The standard Arduino serial interface.
   * - SoftwareSerialIO
     - Arduino serial interface using arbitrary pins.

All plugins have at least the following methods.

.. list-table:: Methods.
   :header-rows: 1

   * - name
     - description
     - parameters
   * -
     - Constructor.
     - user definable
   * - ``begin()``
     - Initialisation function.
     - user definable
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

The methods ``available()``, ``read()`` and ``write()`` are fixed for all
plugins. The constructor and the ``begin()`` function may differ between
plugins.


``HardwareSerialIO``
--------------------

The Arduino hardware has built-in support for serial communication on pins 0
and 1 (which also goes to the computer via the USB connection). The
``HardwareSerialIO`` plugin is a wrapper for the Serial_ library, which allows
communication with the hardware serial interface.

The plugin specific methods are described below.

.. list-table:: Methods.
   :header-rows: 1

   * - name
     - description
     - parameters
   * -
     - Constructor.
     - none
   * - ``begin()``
     - Set the baud rate of the serial connection.
     - ``unsigned long speed``


``SoftwareSerialIO``
--------------------

The SoftwareSerial_ library has been developed to allow serial communication on
other digital pins of the Arduino. The ``SoftwareSerialIO`` plugin is a wrapper
for this library.

The plugin specific methods are described below.

.. list-table:: Methods.
   :header-rows: 1

   * - name
     - description
     - parameters
   * -
     - Constructor, sets the transmit and receive pins.
     - ``uint8_t txPin``, ``uint8_t rxPin``
   * - ``begin()``
     - Set the baud rate of the serial connection.
     - ``unsigned long speed``


.. _Serial: https://www.arduino.cc/en/Reference/Serial
.. _SoftwareSerial: https://www.arduino.cc/en/Reference/SoftwareSerial
