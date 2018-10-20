Device library
=============

Include the header file to use the device library.

.. code:: cpp

    #include <simpleRPC.h>

The library provides the ``interface()`` function, which is responsible for all
serial communication with the host. To use this function, enable serial
communication at 9600 baud in the ``setup()`` body and call the ``interface()``
function in the ``loop()`` body.

.. code:: cpp

    void setup(void) {
      Serial.begin(9600);
    }

    void loop(void) {
      interface();
    }

To export a method, we need to modify the file ``methods.h`` which can be found
in the library code.

- Arduino IDE: ``libraries/simpleRPC/methods.h`` in the ``sketchbook`` folder.
- Ino: ``lib/simpleRPC/simpleRPC/methods.h`` in the root of the project folder.

In this file, we use the ``INTERFACE()`` macro to make a method definition.
This macro takes three or more parameters, depending on the number of
parameters of the method. For each method, we provide a name, a documentation
string, a return type and a list of parameter types. Note that if the method
does not take any parameters, the type ``void`` should be used.

+-------------+-------------------------+
| parameter   | description             |
+=============+=========================+
| 0           | Documentation string.   |
+-------------+-------------------------+
| 1           | Return type.            |
+-------------+-------------------------+
| 2           | Method name.            |
+-------------+-------------------------+
| 3 ..        | Parameter types.        |
+-------------+-------------------------+

The documentation string consists of one field containing the method
description. If applicable, a list of parameter descriptions and a return value
description can be provided by using the ``@P:`` and ``@R:`` prefix
respectively.

+----------------+-------------------------------------+
| field prefix   | description                         |
+================+=====================================+
|                | Method description (first field).   |
+----------------+-------------------------------------+
| ``@P:``        | Parameter description.              |
+----------------+-------------------------------------+
| ``@R:``        | Return value description.           |
+----------------+-------------------------------------+

Example
^^^^^^^

Suppose we want to add a method that takes two parameters and returns one value
like the following one.

.. code:: cpp

    int add(int a, int b) {
      return a + b;
    }

The method definition in ``methods.h`` looks as follows.

.. code:: cpp

    INTERFACE("Add two integers. @P:Value a. @P:Value b. @R:Sum of a and b.",
      int, add, int, int)

We can now build and upload the sketch.


Host library
============

On the host, there are two ways to communicate with the device, either via the
API library, or via the command line.

API Library
-----------

The API library provides the ``Interface`` class. A class instance is made by
passing the path to a serial device.

.. code:: python

    >>> from simple_rpc import Interface
    >>> 
    >>> interface = Interface('/dev/ttyACM0')

Every exported method will show up as a class method of the ``interface``
class instance. These methods can be used like any normal class methods.

Example
^^^^^^^

In our example we have exported the ``add`` method, which is now present as a
class method of the ``interface`` class instance.

.. code:: python

    >>> interface.add(1, 2)
    3

To get more information about this class method, the built-in ``help()``
function can be used.

.. code:: python

    >>> help(interface.add)

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

In our example, the ``list`` subcommand will show a description of the ``add``
method.

.. code::

    $ simple_rpc list
    Available methods:


    add arg0 arg1
        Add two integers.

        arg0 (type int): Value a.
        arg1 (type int): Value b.

        returns (type int): Sum of a and b.

This method can be called by using the ``call`` subcommand.

.. code::

    $ simple_rpc call add 1 2
    3
