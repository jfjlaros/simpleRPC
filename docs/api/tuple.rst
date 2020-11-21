Tuples and Objects
==================

.. code-block:: cpp

    #include "tuple.tcc"

Tuples
------

Tuples can be used to group objects of different types. A Tuple is recursively
defined as being either:

- Empty.
- A pair (``head``, ``tail``), where ``head`` is of an arbitrary type and
  ``tail`` is an other Tuple.

Initialisation of a Tuple can be done with a brace-initializer-list as follows.

.. code-block:: cpp

    Tuple<int, char> t = {10, 'c'};

Element retrieval and assignment is described below in the :ref:`Helper
functions` section.

Note that a Tuple, like any higher order data structure, should be passed by
reference.

Class definitions
~~~~~~~~~~~~~~~~~

.. doxygengroup:: tuple
   :content-only:


Objects
-------

An Object is functionally equivalent to a Tuple, except that its internal
structure is preserved after serialisation. More on serialisation of Objects
can be found in the :ref:`method_discovery` section.

Initialisation of an Object can be done with a brace-initializer-list as
follows.

.. code-block:: cpp

    Object<int, char> o(10, 'c');

Element retrieval and assignment is described below in the :ref:`Helper
functions` section.

Note that an Object, like any higher order data structure, should be passed by
reference.

Class definitions
~~~~~~~~~~~~~~~~~

.. doxygengroup:: object
   :content-only:


Helper functions
----------------

Elements of a Tuple or Object can be retrieved in two ways, either via the
``head`` and ``tail`` member variables, or using with the ``get<>()`` helper
function.

.. code-block:: cpp

    int i = t.head;
    char c = t.tail.head;

    int j = get<0>(t);
    char d = get<1>(t)';

Likewise, assignment of an element can be done via its member variables or with
the ``get<>()`` helper function.

.. code-block:: cpp

    t.head = 11;
    t.tail.head = 'd';

    get<0>(t) = 11;
    get<1>(t) = 'd';

There are additional helper functions available for the creation of Tuples.

The function ``pack()`` can be used to create a temporary Tuple to be used in a
function call.

.. code-block:: cpp

    function(pack('a', 'b', 10));

The ``castStruct()`` function can be used to convert a C ``struct`` to a Tuple.

.. code-block:: cpp

    struct S {
      int i;
      char c;
    };

    S s;
    function(castStruct<int, char>(s));

Functions
~~~~~~~~~

.. doxygengroup:: tuplehelper
   :content-only:
