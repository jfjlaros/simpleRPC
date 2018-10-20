Device library
==============

Include the header file to use the device library.

.. code:: cpp

    #include <simpleRPC.h>

The library provides the ``interface()`` function, which is responsible for all
serial communication with the host. To use this function, enable serial
communication at 9600 baud in the ``setup()`` body and call the ``interface()``
function in the ``loop()`` body.

.. code:: cpp

    void setup(void) {
      Serial.begin(9600);
    }

    void loop(void) {
      interface();
    }

To export a method, we need to modify the file ``methods.h`` which can be found
in the library code.

- Arduino IDE: ``libraries/simpleRPC/methods.h`` in the ``sketchbook`` folder.
- Ino: ``lib/simpleRPC/simpleRPC/methods.h`` in the root of the project folder.

In this file, we use the ``INTERFACE()`` macro to make a method definition.
This macro takes three or more parameters, depending on the number of
parameters of the method. For each method, we provide a name, a documentation
string, a return type and a list of parameter types. Note that if the method
does not take any parameters, the type ``void`` should be used.

+-------------+-------------------------+
| parameter   | description             |
+=============+=========================+
| 0           | Documentation string.   |
+-------------+-------------------------+
| 1           | Return type.            |
+-------------+-------------------------+
| 2           | Method name.            |
+-------------+-------------------------+
| 3 ..        | Parameter types.        |
+-------------+-------------------------+

The documentation string consists of one field containing the method
description. If applicable, a list of parameter descriptions and a return value
description can be provided by using the ``@P:`` and ``@R:`` prefix
respectively.

.. list-table:: Documentation string

    * - field prefix
      - description
    * -
      - Method description (first field).
    * - ``@P:``
      - Parameter description.
    * - ``@R:``
      - Return value description.

Example
^^^^^^^

Suppose we want to add a method that takes two parameters and returns one value
like the following one.

.. code:: cpp

    int add(int a, int b) {
      return a + b;
    }

The method definition in ``methods.h`` looks as follows.

.. code:: cpp

    INTERFACE("Add two integers. @P:Value a. @P:Value b. @R:Sum of a and b.",
      int, add, int, int)

We can now build and upload the sketch.
