Simple RPC implementation for Arduino.
======================================

.. image:: https://img.shields.io/github/last-commit/jfjlaros/simpleRPC.svg
   :target: https://github.com/jfjlaros/simpleRPC/graphs/commit-activity
.. image:: https://travis-ci.org/jfjlaros/simpleRPC.svg?branch=master
   :target: https://travis-ci.org/jfjlaros/simpleRPC
.. image:: https://readthedocs.org/projects/simplerpc/badge/?version=latest
   :target: https://simpleRPC.readthedocs.io/en/latest
.. image:: https://img.shields.io/github/release-date/jfjlaros/simpleRPC.svg
   :target: https://github.com/jfjlaros/simpleRPC/releases
.. image:: https://img.shields.io/github/release/jfjlaros/simpleRPC.svg
   :target: https://github.com/jfjlaros/simpleRPC/releases
.. image:: https://www.ardu-badge.com/badge/simpleRPC.svg
   :target: https://www.ardu-badge.com/simpleRPC
.. image:: https://img.shields.io/github/languages/code-size/jfjlaros/simpleRPC.svg
   :target: https://github.com/jfjlaros/simpleRPC
.. image:: https://img.shields.io/github/languages/count/jfjlaros/simpleRPC.svg
   :target: https://github.com/jfjlaros/simpleRPC
.. image:: https://img.shields.io/github/languages/top/jfjlaros/simpleRPC.svg
   :target: https://github.com/jfjlaros/simpleRPC
.. image:: https://img.shields.io/github/license/jfjlaros/simpleRPC.svg
   :target: https://raw.githubusercontent.com/jfjlaros/simpleRPC/master/LICENSE.md

----

This library provides a simple way to export Arduino_ functions as remote
procedure calls. The exported method definitions are communicated to the host,
which is then able to generate an API interface.

**Features:**

- For each method, only one line of code is needed for exporting.
- Automatic parameter- and return type inference.
- Support for all native C types and strings.
- Support for arbitrary functions and class methods.
- Optional function and parameter naming and documentation.
- Support for PROGMEM_'s ``F()`` macro to reduce memory footprint.
- Support for compound data structures like Tuples, Objects (Tuples with
  internal structure), Vectors and arbitrary combinations of these.
- Support for reading multidimensional C arrays (e.g., ``int**``).
- Support for different types of I/O interfaces via plugins, e.g.,

  - Bluetooth.
  - Ethernet (untested).
  - Hardware serial.
  - RS485 serial.
  - Software serial (untested).
  - USB serial.
  - WiFi.
  - Wire (untested).

- Support for using multiple interfaces at the same time.

The Arduino library is independent of any host implementation, a Python API
client_ library is provided as a reference implementation.

Please see ReadTheDocs_ for the latest documentation.


Quick start
-----------

Export any function e.g., ``digitalRead()`` and ``digitalWrite()`` using the
``interface()`` function.

.. code-block:: cpp

    #include <simpleRPC.h>

    void setup(void) {
      Serial.begin(9600);
    }

    void loop(void) {
      interface(Serial, digitalRead, "", digitalWrite, "");
    }

These functions are now available on the host under names ``method0()`` and
``method1()``.

The documentation string can be used to name and describe the method.

.. code-block:: cpp

    interface(
      Serial,
      digitalRead,
        "digital_read: Read digital pin. @pin: Pin number. @return: Pin value.",
      digitalWrite,
        "digital_write: Write to a digital pin. @pin: Pin number. @value: Pin value.");

This is reflected on the host, where the methods are now named
``digital_read()`` and ``digital_write()`` and where the provided API
documentation is also available. In the client reference implementation
documentation, contains an example_ on how this works.


Further reading
---------------

Please read :doc:`usage` for more information about exporting normal
functions, class member functions and documentation conventions.

If you want to create your own host library implementation for other
programming languages, the section :doc:`protocol` should help you on your way.


.. _Arduino: https://www.arduino.cc
.. _PROGMEM: https://www.arduino.cc/reference/en/language/variables/utilities/progmem/
.. _ReadTheDocs: https://simpleRPC.readthedocs.io
.. _client: https://arduino-simple-rpc.readthedocs.io
.. _example: https://arduino-simple-rpc.readthedocs.io/en/latest/#quick-start
