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
