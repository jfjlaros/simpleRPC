Function Signatures
===================

.. code-block:: cpp

    #include "signature.tcc"

.. list-table:: Function signature examples.
   :header-rows: 1

   * - signature
     - encoding
     - description
   * - ``short int f(char, float)``
     - ``h: c f``
     - Function that returns a value.
   * - ``void f(char, float)``
     - ``: c f``
     - Function that does not return a value.
   * - ``void f(Tuple<int, char>&, float)``
     - ``: ic f``
     - A Tuple parameter.
   * - ``Object<int, char> f(float)``
     - ``(ic): f``
     - Returning an Object.
   * - ``int f(Vector<signed char>&, int)``
     - ``i: [b] i``
     -  A Vector parameter.

Functions
---------

.. doxygengroup:: signature
   :content-only:
