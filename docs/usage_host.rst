Host library
============

On the host, there are two ways to communicate with the device, either via the
API library, or via the command line.


API Library
-----------

The API library provides the ``Interface`` class. A class instance is made by
passing the path to a serial device to the constructor.

.. code:: python

    >>> from simple_rpc import Interface
    >>> 
    >>> interface = Interface('/dev/ttyACM0')

Every exported method will show up as a class method of the ``interface`` class
instance. These methods can be used like any normal class methods.
Alternatively, the exported methods can be called by name using the
``call_method()`` function.

The constructor takes the following parameters.

.. list-table:: Constructor parameters.
   :header-rows: 1

   * - name
     - optional
     - description
   * - ``device``
     - no
     - Serial device name.
   * - ``baudrate``
     - yes
     - Baud rate.
   * - ``wait``
     - yes
     - Time in seconds before communication starts.
   * - ``autoconnect``
     - yes
     - Automatically connect.

The following standard methods are available.

.. list-table:: Class methods.
   :header-rows: 1

   * - name
     - description
   * - ``open()``
     - Connect to serial device.
   * - ``close()``
     - Disconnect from serial device.
   * - ``is_open()``
     - Query serial device state.
   * - ``call_method()``
     - Execute a method.

If the connection should not be made instantly, the ``autoconnect`` parameter
can be used in combination with the ``open()`` function.

.. code:: python

    >>> interface = Interface('/dev/ttyACM0', autoconnect=False)
    >>> # Do something.
    >>> interface.open()

The connection state can be queried using the ``is_open()`` function and it can
be closed using the ``close()`` function.

.. code:: python

    >>> if interface.is_open():
    >>>     interface.close()

Additionally, the ``with`` statement is supported for easy opening and closing.

.. code:: python

    >>> with Interface('/dev/ttyACM0') as interface:
    >>>     interface.version()

Example
^^^^^^^

In our example we have exported the ``inc`` method, which is now present as a
class method of the ``interface`` class instance.

.. code:: python

    >>> interface.inc(1)
    2

Alternatively, the exported method can be called using the ``call_mathod()``
function.

.. code:: python

    >>> interface.call_method('inc', 1)
    2

To get more information about this class method, the built-in ``help()``
function can be used.

.. code:: python

    >>> help(interface.inc)
    Help on method inc:

    inc(a) method of simple_rpc.simple_rpc.Interface instance
        Increment a value.

        :arg int a: Value.

        :returns int: a + 1.


Command line interface
----------------------

The command line interface can be useful for method discovery and testing
purposes. It currently has two subcommands: ``list``, which shows a list of
available methods and ``call`` for calling methods. For more information, use
the ``-h`` option.

.. code::

    simple_rpc -h

Example
^^^^^^^

In our example, the ``list`` subcommand will show a description of the ``inc``
method and the ``set_led`` method.

.. code::

    $ simple_rpc list
    Available methods:


    inc a
        Increment a value.

        int a: Value.

        returns int: a + 1.


    set_led brightness
        Set LED brightness.

        int brightness: Brightness.


A method can be called by using the ``call`` subcommand.

.. code::

    $ simple_rpc call inc 1
    2
