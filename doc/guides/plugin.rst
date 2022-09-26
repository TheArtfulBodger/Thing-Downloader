Plugin Creator's Guide
======================

This guide is a very simple 


Creating
--------

If it's a relatively simple plugin, it should be contained in a single file, if it's larger, I'd reccommend creating a folder in ``plugins``.

CMake
^^^^^

This project uses CMake for building, so you will need to add the jobs to the build 

If this is a single-file plugin, you can add the following to ``plugins/CMakeLists.txt``

.. code-block:: cmake

    add_library(apod SHARED apod.cpp)
    target_compile_features(apod PUBLIC cxx_std_17)
    target_link_libraries(apod cpr::cpr)

A larger plugin would require a more complex ``CMakeLists.txt`` file, but don't forget the ``add_subdirectory`` command.

Dependencies
^^^^^^^^^^^^

The existing plugins use a number of dependencies already, and adding additional ones should be avoided.

* `cpr <https://libcpr.org>`_ (for web requests)
* `subprocess <https://github.com/tsaarni/cpp-subprocess>`_ [#]_
* `JSON for Modern C++ <https://github.com/nlohmann/json>`_
* `Gumbo Query <https://github.com/Falven/gumbo-query>`_ (for web scraping)
* `TinyXML2 <https://github.com/Falven/gumbo-query>`_ (for web scraping)

.. [#] **NB:** This may get replaced with a modified version of `Boost.Process <https://www.boost.org/doc/libs/1_80_0/doc/html/process.html>`_


Definition
^^^^^^^^^^

.. note::
    These Functions should operate as fully encapsulated functions,
    using no global state, and all job properties should be stored in the buffer,
    and secrets and configuration in the downloader object.

:ref:`You need to define the following variables and function <plugin functions>`


Documenting
-----------

Create an ``key.rst`` file in the plugins folder (The content of ``identity.rst`` and ``apod.rst`` should be useful as a template).

If it uses an undocumented (or reverse-engineered) API, the documentation should contain documentation for the routes used (Like with :doc:`/plugins/itchio`)