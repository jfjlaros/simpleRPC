Vectors
=======

.. code-block:: cpp

    #include "vector.tcc"

A Vector is a sequence container that implements storage of data elements. The
type of the vector is given at initialisation time via a template parameter,
e.g., ``int``.

.. code-block:: cpp

    Vector<int> v;
    Vector<int> u(12);

In this example, Vector ``v`` is of size 0 and ``u`` is of size 12. A Vector
can also be initialised with a pointer to an allocated block of memory.

.. code-block:: cpp

    Vector<int> v(12, data);

The memory block is freed when the Vector is destroyed. If this is not
desirable, an additional flag ``destroy`` can be passed to the constructor as
follows.

.. code-block:: cpp

    Vector<int> v(12, data, false);

This behaviour can also be changed by manipulating the ``destroy`` member
variable.

A Vector can be resized using the ``resize`` method.

.. code-block:: cpp

    v.resize(20);

The ``size`` member variable contains the current size of the Vector.

Element retrieval and assignment is done in the usual way.

.. code-block:: cpp

    int i = v[10];

    v[11] = 9;

Note that a Vector, like any higher order data structure, should be passed by
reference.

Class definition
----------------

.. doxygengroup:: vector
   :content-only:
