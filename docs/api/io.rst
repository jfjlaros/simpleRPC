Input / output
==============

Convenience functions for reading and writing. A template class ``I``, is used
as an abstraction for I/O devices like serial ports, wire interfaces and
network interfaces like ethernet. An overview of the required methods of an I/O
plugin is described in the :doc:`plugins` section.


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
