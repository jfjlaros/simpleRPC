Input / output
==============

Convenience functions for reading and writing. A template class ``I``, is used
as an abstraction for I/O devices like serial ports, wire interfaces and
network interfaces like ethernet. An overview of the required methods of an I/O
plugin is described in the :doc:`plugins` section.


Printing
--------

.. code-block:: cpp

    #include "print.tcc"

The following functions take care of serialisation of:

- Values of basic types.
- C strings (``char[]``, ``char*``, ``char const[]``, ``char const*``).
- C++ Strings.
- PROGMEM strings (``F()`` macro).

Finally, a print function that takes an arbitrary amount of parameters is
provided for convenience.

Functions
~~~~~~~~~

.. doxygengroup:: print
   :content-only:


Reading
-------

Read functions for deserialisation.

.. code-block:: cpp

    #include "read.tcc"

Functions
~~~~~~~~~

.. doxygengroup:: read
   :content-only:


Writing
-------

Write functions for serialisation.

.. code-block:: cpp

    #include "read.tcc"

Functions
~~~~~~~~~

.. doxygengroup:: write
   :content-only:
