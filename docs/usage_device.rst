Device library
==============

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

Methods are exported by calling the ``interface()`` function from the
``loop()`` body. This function accepts a list of tuples (function,
documentation string) as parameters.

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

A documentation string consists of a method name and a field containing the
method description. If applicable, a list of parameter descriptions and a
return value description can be provided by using the ``@P:`` and ``@R:``
prefix respectively.

.. list-table:: Documentation string.
   :header-rows: 1

   * - field prefix
     - description
     - field suffix
   * -
     - Method name.
     - ``:``
   * -
     - Method description.
     -
   * - ``@P:``
     - Parameter description.
     -
   * - ``@R:``
     - Return value description.
     -

Example
^^^^^^^

Suppose we want to export a method that sets the brightness of an LED and a
method that takes two parameters and returns one value.

.. code:: cpp

    void setLed(byte brightness) {
      analogWrite(13, brightness);
    }

    int add(int a, int b) {
      return a + b;
    }

Exporting these methods in the ``loop()`` body looks as follows:

.. code:: cpp

    void loop(void) {
      interface(
        setLed, "set_led: Set LED brightness. @P:Brightness.",
        add, "add: Add two integers. @P:Value a. @P:Value b. @R:Sum of a and b.");
    }

We can now build and upload the sketch.
