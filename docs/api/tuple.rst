Tuples
======

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

    Tuple<int, char> t {10, 'c'};

Element retrieval and assignment is described below in the :ref:`Helper
functions` section.

Class definitions
~~~~~~~~~~~~~~~~~

.. doxygengroup:: tuple
   :content-only:


Helper functions
----------------

Elements of a Tuple can be retrieved in two ways, either via the ``head`` and
``tail`` member variables, or using with the ``get<>()`` helper function.

.. code-block:: cpp

    int i = t.head;
    char c = t.tail.head;

    int j = get<0>(t);
    char d = get<1>(t);

Likewise, assignment of an element can be done via its member variables or with
the ``get<>()`` helper function.

.. code-block:: cpp

    t.head = 11;
    t.tail.head = 'd';

    get<0>(t) = 11;
    get<1>(t) = 'd';

The function ``makeTuple()`` can be used to create a temporary Tuple to be used in a
function call.

.. code-block:: cpp

    function(makeTuple('a', 'b', 10));


Functions
~~~~~~~~~

.. doxygengroup:: tuplehelper
   :content-only:
