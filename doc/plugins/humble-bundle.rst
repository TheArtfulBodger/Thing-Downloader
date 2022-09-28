Humble Bundle Downloader
========================


Simple plugin to download the user's library from `Humble Bundle <https://www.humblebundle.com/>`_, based on `this project <https://github.com/xtream1101/humblebundle-downloader>`_

.. list-table::

 * - **Name**
   - Humble Bundle
 * - **Description**
   - Download games and downloadables from Humble Bundle
 * - **Key**
   - humble-bundle
 * - **Required Configurations**
   - None
 * - **Required Secrets**
   - ``_SIMPLEAUTH_SESS`` - the value of the ``_simpleauth_sess`` cookie for a browser logged into the humble account

How it works
------------

Get Jobs Stage
^^^^^^^^^^^^^^

The script makes a ``GET`` request to ``https://www.humblebundle.com/home/library``. In the ``#user-home-json-data`` element, there is a JSON object, contining amongst other things (wishlist etc. ) the list of order game keys.

For each key, a request is made to ``https://www.humblebundle.com/api/v1/order/{KEY}?all_tpkds=true``, which contains a list of products in the order under the key ``subproducts``.

Download Jobs
^^^^^^^^^^^^^

Each object has a list of ``downloads`` for each downloadable items. Sometimes a job will have multiple entries in the ``download_struct`` entry for multiple copies of the file (eg, PDF and EPUB versions of a book) 