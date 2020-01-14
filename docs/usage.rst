Usage
=====

Include the header file to use the device library.

.. code:: cpp

    #include <simpleRPC.h>

The library provides the ``interface()`` function, which is responsible for all
communication with the host. To use this function, first define which interface
to use by instantiating one of the plugins, the ``HardwareSerialIO`` for
example.

.. code:: cpp

    HardwareSerialIO io;

This particular plugin needs to be initialised with the standard ``Serial``
class instance to enable communication using the hardware serial interface.
This is done using the ``begin()`` method in the ``setup()`` body.

.. code:: cpp

    void setup(void) {
      Serial.begin(9600);
      io.begin(Serial);
    }

For other I/O interfaces, please see doc:`plugins`.


Standard methods
----------------

Methods are exported by calling the ``interface()`` function from the
``loop()`` body. This function accepts (function, documentation) pairs as
parameters.

.. list-table:: Interface function parameters.
   :header-rows: 1

   * - parameter
     - description
   * - 0
     - Input / output class instance.
   * - 1
     - Method one.
   * - 2
     - Documentation string of method one.
   * - 3
     - Method two.
   * - 4
     - Documentation string of method two.
   * - ...
     - ...

A documentation string consists of a list of key-value pairs in the form ``key:
value`` delimited by the ``@`` character. The first pair in this list is
reserved for the method name and its description, all subsequent pairs are used
to name and describe parameters or to describe a return value.

.. list-table:: Documentation string.
   :header-rows: 1

   * - field prefix
     - key
     - value
   * -
     - Method name.
     - Method description.
   * - ``@``
     - Parameter name.
     - Parameter description.
   * - ``@``
     - ``return``
     - Return value description.

The documentation string may be incomplete or empty. The following defaults are
used for missing keys. All descriptions may be empty.

.. list-table:: Default names.
   :header-rows: 1

   * - key
     - default
   * - Method name.
     - ``method`` followed by a number, e.g., ``method0``.
   * - Parameter name.
     - ``arg`` followed by a number, e.g., ``arg0``.
   * - ``return``
     - ``return``

To reduce the memory footprint, the use of the ``F()`` macro is allowed in the
``interface()`` function. This stores the documentation string in program
memory instead of SRAM. For more information, see the progmem_ documentation.

Example
^^^^^^^

Suppose we want to export a method that sets the brightness of an LED and a
method that takes one parameter and returns a value.

.. code:: cpp

    void setLed(byte brightness) {
      analogWrite(LED_BUILTIN, brightness);
    }

    int inc(int a) {
      return a + 1;
    }

Exporting these methods in the ``loop()`` body looks as follows:

.. code:: cpp

    void loop(void) {
      interface(
        io,
        inc, "inc: Increment a value. @a: Value. @return: a + 1.",
        setLed, "set_led: Set LED brightness. @brightness: Brightness.");
    }

We can now build and upload the sketch.

The client reference documentation includes an example_ on how these methods
can be accessed from the host.


Class methods
-------------

Class member functions are different from ordinary functions in the sense that
they always operate on an object. This is why it is not possible to simply pass
a function pointer, but to also provide a class instance for the function to
operate on. To facilitate this, the ``pack()`` function can be used to combine
a class instance and a function pointer before passing them to ``interface()``.

For a class instance ``c`` of class ``C``, the class member function ``f()``
can be packed as follows:

.. code:: cpp

    pack(&c, &C::f)

The result can be passed to ``interface()``.

Example
^^^^^^^

Suppose we have a library named *led* which provides the class ``LED``. This
class has a member function named ``setBrightness``.

.. code:: cpp

    #include "led.h"

    LED led(LED_BUILTIN);


Exporting this class method as a remote call goes as follows:

.. code:: cpp

      void loop(void) {
        interface(
          io,
          pack(&led, &LED::setBrightness),
            "set_led: Set LED brightness. @brightness: Brightness.");
      }


Tuples
------

Tuples can be used to group multiple objects of different types together. A
Tuple has two members, ``head`` and ``tail``, where ``head`` is of any type,
and ``tail`` is an other Tuple.

Tuples can be initialised with a brace-initializer-list as follows.

.. code:: cpp

    Tuple<int, char> t = {10, 'c'};

Elements of a Tuple can be retrieved in two ways, either via its ``head`` and
``tail`` member variables, or with the ``get<>()`` helper function.

.. code:: cpp

    int i = t.head;
    char c = t.tail.head;

    int j = get<0>(t);
    char d = get<1>(t)';

Likewise, assignment of an element can be done via its member variables or with
the ``get<>()`` helper function.

.. code:: cpp

    t.head = 11;
    t.tail.head = 'd';

    get<0>(t) = 11;
    get<1>(t) = 'd';

There are two additional helper functions available for Tuples: ``pack()`` and
``castStruct()``. ``pack()`` can be used to create a temporary tuple to be used
in a function call.

.. code:: cpp

    function(pack('a', 'b', 10));

Likewise, the ``castStruct()`` function can be used to convert a C ``struct``
to a Tuple.

.. code:: cpp

    struct S {
      int i;
      char c;
    };

    S s;
    function(castStruct<int, char>(s));

Note that a Tuple, like any higher order data structure should be passed by
reference.


Objects
-------

Objects behave much like Tuples, but they are serialised differently (see the
:doc:`protocol` section).

Objects can be initialised via a constructor as follows.

.. code:: cpp

    Object<int, char> o(10, 'c');

Element retrieval and assignment is identical to that of Tuples.

Note that an Object, like any higher order data structure should be passed by
reference.

Vectors
-------

A Vector is a sequence container that implements storage of data elements. The
type of the vector is given at initialisation time via a template parameter,
e.g., ``int``.

.. code:: cpp

    Vector<int> v;
    Vector<int> u(12);

In this example, Vector ``v`` is of size 0 and ``u`` is of size 12. A Vector
can also be initialised with a pointer to an allocated block of memory.

.. code:: cpp

    Vector<int> v(12, data);

The memory block is freed when the Vector is destroyed. If this is not
desirable, an additional flag ``destroy`` can be passed to the constructor as
follows.

.. code:: cpp

    Vector<int> v(12, data, false);

This behaviour can also be changed by manipulating the ``destroy`` member
variable.

A Vector can be resized using the ``resize`` method.

.. code:: cpp

    v.resize(20);

The ``size`` member variable contains the current size of the Vector.

Element retrieval and assignment is done in the usual way.

.. code:: cpp

    int i = v[10];

    v[11] = 9;

Note that a Vector, like any higher order data structure should be passed by
reference.


Complex objects
---------------

Arbitrary combinations of Tuples, Objects and Vectors can be made to construct
complex objects.

In the following example, we create a 2-dimensional matrix of integers, a
Vector of Tuples and an Object containing an integer, a Vector and an other
Object respectively.

.. code:: cpp

    Vector<Vector<int> > matrix;

    Vector<Tuple<int, char> > v;

    Object<int, Vector<int>, Object<char, long> > o;


.. _example: https://arduino-simple-rpc.readthedocs.io/en/latest/library.html#example
.. _progmem: https://www.arduino.cc/reference/en/language/variables/utilities/progmem/
