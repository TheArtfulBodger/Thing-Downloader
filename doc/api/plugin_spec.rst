Plugin Specification
====================

This contains the documentation for **Version 1** of the plugin specification

Plugin Funcions
---------------
A plugin needs the following values defined

.. warning::
    These need to be declared with C linkage (in an `extern "C"` block) to avoid C++ name mangling.

    Unfortunately, compilers seem **not** raise errors or warnings if not all of these values are defined.    

Variables
"""""""""

.. doxygenvariable:: key
.. doxygenvariable:: name
.. doxygenvariable:: description
.. doxygenvariable:: required_confs
.. doxygenvariable:: required_secrets
.. doxygenvariable:: version

Functions
"""""""""

.. note::
    These Functions should operate as fully encapsulated functions,
    using no global state, and all job properties should be stored in the buffer,
    and secrets and configuration in the downloader object.

.. doxygenfunction:: process_job(const td::dl& base, const td::job& job)
.. doxygenfunction:: should_skip(const td::dl& base, const td::job& job)
.. doxygenfunction:: get_jobs(const td::dl &base)

Abstract Classes & Typedefs
---------------------------

These are abstract classes, where smart pointers will be used as arguments 

.. doxygenclass:: td::job_base
   :members:

.. doxygenclass:: td::downloader_base
   :members:

.. doxygentypedef:: td::dl
.. doxygentypedef:: td::job