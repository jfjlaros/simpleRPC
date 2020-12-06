Usage
=====

Include the header file to use the simpleRPC library.

.. code-block:: cpp

    #include <simpleRPC.h>

The library provides the ``interface()`` function, which is responsible for all
communication with the host. To use this function, first initialize the standard
``Serial`` class instance to enable communication using the hardware serial
interface. This is done using the ``begin()`` method in the ``setup()`` body.

.. code-block:: cpp

    void setup(void) {
      Serial.begin(9600);
    }

Please see the :doc:`plugins` section for using other I/O interfaces.


Exporting C functions
---------------------

Standard C functions are exported as RPC methods by calling the ``interface()``
function from the ``loop()`` body. This function accepts (function,
documentation) pairs as parameters.

.. list-table:: Interface function parameters.
   :header-rows: 1

   * - parameter
     - description
   * - 0
     - I/O class instance.
   * - 1
     - Function one.
   * - 2
     - Documentation string of function one.
   * - 3
     - Function two.
   * - 4
     - Documentation string of function two.
   * - ...
     - ...

A documentation string consists of a list of key-value pairs in the form ``key:
value`` delimited by the ``@`` character. The first pair in this list is
reserved for the RPC method name and its description, all subsequent pairs are
used to name and describe parameters or to describe a return value.

.. list-table:: Documentation string.
   :header-rows: 1

   * - field prefix
     - key
     - value
   * -
     - RPC method name.
     - RPC method description.
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
   * - RPC method name.
     - ``method`` followed by a number, e.g., ``method0``.
   * - Parameter name.
     - ``arg`` followed by a number, e.g., ``arg0``.
   * - ``return``
     - ``return``

To reduce the memory footprint, the ``F()`` macro can be used in the
``interface()`` function. This stores the documentation string in program
memory instead of SRAM. For more information, see the progmem_ documentation.

Example
^^^^^^^

Suppose we want to export a function that sets the brightness of an LED and a
function that takes one parameter and returns a value.

.. code-block:: cpp

    void setLed(byte brightness) {
      analogWrite(LED_BUILTIN, brightness);
    }

    int inc(int a) {
      return a + 1;
    }

Exporting these functions goes as follows:

.. code-block:: cpp

    void loop(void) {
      interface(
        Serial,
        inc, "inc: Increment a value. @a: Value. @return: a + 1.",
        setLed, "set_led: Set LED brightness. @brightness: Brightness.");
    }

We can now build and upload the sketch.

The client reference documentation includes an example_ on how these methods
can be accessed from the host.


Exporting class methods
-----------------------

Class methods are different from ordinary functions in the sense that they
always operate on an object. This is why both a function pointer and a class
instance need to be provided to the ``interface()`` function. To facilitate
this, the ``pack()`` function can be used to combine a class instance and a
function pointer before passing them to ``interface()``.

For a class instance ``c`` of class ``C``, the class method ``f()``
can be packed as follows:

.. code-block:: cpp

    pack(&c, &C::f)

The result can be passed to ``interface()``.

Example
^^^^^^^

Suppose we have a library named *led* which provides the class ``LED``. This
class has a method named ``setBrightness``.

.. code-block:: cpp

    #include "led.h"

    LED led(LED_BUILTIN);


Exporting this class method goes as follows:

.. code-block:: cpp

      void loop(void) {
        interface(
          Serial,
          pack(&led, &LED::setBrightness),
            "set_led: Set LED brightness. @brightness: Brightness.");
      }


Complex objects
---------------

In some cases, basic C types and C strings are not sufficient or convenient.
This is why simpleRPC supports higher order objects described in detail in the
:doc:`api/tuple` and :doc:`api/vector` sections.

Arbitrary combinations of these higher order objects can be made to construct
complex objects.

In the following example, we create a 2-dimensional matrix of integers, a
Vector of Tuples and an Object containing an integer, a Vector and an other
Object respectively.

.. code-block:: cpp

    Vector<Vector<int> > matrix;

    Vector<Tuple<int, char> > v;

    Object<int, Vector<int>, Object<char, long> > o;

These objects can be used for parameters as well as for return values. Note
that these objects, like any higher order data structure should be passed by
reference.


C arrays
--------

Passing a C array as a parameter is supported, but since in general it is not
possible to deduce the size or internal structure of an object it is not
possible to return a C array. The closely related Vector should be used in this
case.

In the following example, an integer C array is passed to a function.

.. code-block:: cpp

    void readArray(int* a) {}

Multidimensional arrays are implemented as ``NULL`` terminated arrays of
pointers. This allows for structures that do not have a fixed length in any
dimension, e.g., a two-dimensional array ``int**`` does not have to be
rectangular.


.. _example: https://arduino-simple-rpc.readthedocs.io/en/latest/library.html#example
.. _progmem: https://www.arduino.cc/reference/en/language/variables/utilities/progmem/
