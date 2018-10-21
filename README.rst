Simple RPC implementation for Arduino.
======================================

.. image:: https://img.shields.io/github/last-commit/jfjlaros/simpleRPC.svg
   :target: https://github.com/jfjlaros/simpleRPC/graphs/commit-activity
.. image:: https://readthedocs.org/projects/simplerpc/badge/?version=latest
   :target: https://simpleRPC.readthedocs.io/en/latest
.. image:: https://img.shields.io/github/release-date/jfjlaros/simpleRPC.svg
   :target: https://github.com/jfjlaros/simpleRPC/releases
.. image:: https://img.shields.io/github/release/jfjlaros/simpleRPC.svg
   :target: https://github.com/jfjlaros/simpleRPC/releases
.. image:: https://img.shields.io/pypi/v/arduino-simple-rpc.svg
   :target: https://pypi.org/project/arduino-simple-rpc/
.. image:: https://img.shields.io/github/languages/code-size/jfjlaros/simpleRPC.svg
   :target: https://github.com/jfjlaros/simpleRPC
.. image:: https://img.shields.io/github/languages/count/jfjlaros/simpleRPC.svg
   :target: https://github.com/jfjlaros/simpleRPC
.. image:: https://img.shields.io/github/languages/top/jfjlaros/simpleRPC.svg
   :target: https://github.com/jfjlaros/simpleRPC
.. image:: https://img.shields.io/github/license/jfjlaros/simpleRPC.svg
   :target: https://raw.githubusercontent.com/jfjlaros/simpleRPC/master/LICENSE.md

----

This library provides a simple way for programmers to export Arduino_ functions
as remote procedure calls. The exported method definitions are communicated to
the host, which is then able to generate an API interface.

For each method, only one additional line of code is needed for exporting. On
the host, only one function call is needed to perform a remote procedure call.

The Arduino library is independent of any host implementation, we provide a
Python API library as a reference implementation.

Please see ReadTheDocs_ for the latest documentation.


.. _Arduino: https://www.arduino.cc
.. _ReadTheDocs: https://simpleRPC.readthedocs.io/en/latest/index.html
