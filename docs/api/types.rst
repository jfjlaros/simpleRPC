Types
=====

.. code-block:: cpp

    #include "types.tcc"

Get a struct_ formatted representation of the type of a value.

.. list-table:: Type encoding examples.
   :header-rows: 1

   * - type
     - encoding
     - description
   * - ``bool``
     - ``?``
     - Boolean.
   * - ``unsigned long int``
     - ``L``
     - Unsigned integer.
   * - ``char const*``
     - ``s``
     - String.
   * - ``Tuple<int, signed char, unsigned long>``
     - ``ibL``
     - Tuple (no internal structure).
   * - ``Object<Object<char, int>, unsigned long>``
     - ``((ci)L)``
     - Object (internal structure is preserved).
   * - ``Vector<int>``
     - ``[i]``
     - Vector.

Functions
---------

.. doxygengroup:: types
   :content-only:

STL functions
^^^^^^^^^^^^^

The following functions are only available for cores that have support for the
C++ STL. See the :doc:`stl` section for more information.

.. doxygengroup:: STLTypes
   :content-only:


.. _struct: https://docs.python.org/3.5/library/struct.html#format-strings
