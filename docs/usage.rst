Usage
=====

Device
------

.. code:: cpp

    #include <simpleRPC.h>

.. code:: cpp

    void setup(void) {
      Serial.begin(9600);
    }

    void loop(void) {
      interface();
    }

.. code:: cpp

    int add(int a, int b) {
      return a + b;
    }

.. code:: cpp

    INTERFACE("Add two integers. @P:Value a. @P:Value b. @R:Sum of a and b.",
      int, add, int, int)

Host
----

Library
~~~~~~~

.. code:: python

    >>> from simple_rpc import Interface
    >>> 
    >>> interface = Interface('/dev/ttyACM0')
    >>> interface.add(1, 2)
    3


.. code:: python

    >>> help(interface.add)

Command line interface
~~~~~~~~~~~~~~~~~~~~~~

.. code::

    $ simple_rpc list
    Available methods:


    add arg0 arg1
        Add two integers.

        arg0 (type int): Value a.
        arg1 (type int): Value b.

        returns (type int): Sum of a and b.

.. code::

    $ simple_rpc call add 1 2
    3
