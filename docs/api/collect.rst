String collector
================

.. code-block:: cpp

    #include "collect.tcc"

A Collector is used to collect ``char const*`` strings in order to write them
to an input / output object at a later stage.

.. code-block:: cpp

    Collector col;

.. code-block:: cpp

    col.add("hello");

.. code-block:: cpp

    col.print(io);


Class definition
----------------

.. doxygengroup:: collector
   :content-only:
