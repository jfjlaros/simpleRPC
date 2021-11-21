Standard Template Library
=========================

Some cores like the SAM core and the ESP32 core have support for the C++
Standard Template Library which provides some useful STL_ containers. Currently
the following STL containers can be used in RPC calls.

- Arrays_.
- Strings_.
- Tuples_.
- Vectors_.

Installation
------------

The ESP32 core supports the STL by default. For the SAM core, some
modifications need to be made to the platform configuration file.

First locate your arduino_ configuration folder, navigate to
``packages/arduino/hardware/sam/x.y.z`` (where ``x.y.z`` is a version string
e.g., ``1.6.12``).

Open the file ``platform.txt`` and search for the line starting with
``recipe.c.combine.pattern``, add ``-lstdc++ -specs=nano.specs`` to the end of
this line.

Usage
-----

Include the following header file instead of the standard one.

.. code-block:: cpp

    #include <simpleRPC_STL.h>

Example
-------

See the esp32_stl_ sketch for an example.


.. _STL: https://www.cplusplus.com/reference/stl/
.. _Arrays: https://www.cplusplus.com/reference/array/
.. _Strings: https://www.cplusplus.com/reference/string/
.. _Tuples: https://www.cplusplus.com/reference/tuple/
.. _Vectors: https://www.cplusplus.com/reference/vector/
.. _arduino: https://support.arduino.cc/hc/en-us/articles/360018448279-Where-can-I-find-the-Arduino15-folder-
.. _esp32_stl: https://github.com/jfjlaros/simpleRPC/blob/master/examples/esp32_stl/esp32_stl.ino
