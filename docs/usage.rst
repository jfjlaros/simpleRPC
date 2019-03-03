Library
=======

Include the header file to use the device library.

.. code:: cpp

    #include <simpleRPC.h>

The library provides the ``interface()`` function, which is responsible for all
serial communication with the host. To use this function, first enable serial
communication at 9600 baud in the ``setup()`` body.

.. code:: cpp

    void setup(void) {
      Serial.begin(9600);
    }


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
     - Method one.
   * - 1
     - Documentation string of method one.
   * - 2
     - Method two.
   * - 3
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
     - ``method`` followed by a number, e.g., ``method2``.
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
      analogWrite(13, brightness);
    }

    int inc(int a) {
      return a + 1;
    }

Exporting these methods in the ``loop()`` body looks as follows:

.. code:: cpp

    void loop(void) {
      interface(
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

    LED led(13);


Exporting this class method as a remote call goes as follows:

.. code:: cpp

      void loop(void) {
        interface(
          pack(&led, &LED::setBrightness),
            "set_led: Set LED brightness. @brightness: Brightness.");
      }


.. _example: https://arduino-simple-rpc.readthedocs.io/en/latest/library.html#example
.. _progmem: https://www.arduino.cc/reference/en/language/variables/utilities/progmem/
