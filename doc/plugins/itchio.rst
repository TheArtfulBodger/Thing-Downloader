Itch.io Plugin
==============

This plugin downloads downloads from `itch.io <https://itch.io>`_.

.. list-table::

 * - **Name**
   - Itch.Io
 * - **Description**
   - Download games and downloadables from itch.io
 * - **Key**
   - itchio
 * - **Required Configurations**
   - None
 * - **Required Secrets**
   - ``API_KEY`` API Key from `itch.io website <https://itch.io/user/settings/api-keys>`_

How it works
------------

Get Jobs Stage
^^^^^^^^^^^^^^

The script loads the user's libary (one page at a time) using the :ref:`Owned Keys API Route<Getting The Library>`


Download Jobs
^^^^^^^^^^^^^


Load Downloadables For Game
"""""""""""""""""""""""""""
This stage uses the :ref:`Metadata<Get Metadata for a game>` and :ref:`Upload<Get Downloadable Items>` routes to write ``DIR/PUBLISHER/GAME.json`` and populate the job queue with the uploads.

Download a File
"""""""""""""""

This stage uses the :ref:`Downloading an Item` API route to download the file to the path ``DIR/PUBLISHER/GAME/FILE``, and will write a hash file to ``DIR/PUBLISHER/GAME/FILE.md5``. This will save time redownloading, and allow the saving of multiple versions.

.. warning::
    Some Games give Google Drive links for downloads. These will probably fail for the time being.


API Reverse Engineered
----------------------

This API was reverse engineered from the `desktop
app <https://itch.io/app>`__ using a web proxy (set ``HTTP_PROXY`` env)

Logging in
^^^^^^^^^^

This is mostly redundant as this only generates an API key.

* POST ``https://api.itch.io/login``
* **URL-Encoded Form**

  * ``username``  the user's username
  * ``passsword``  the user's passsword
  * ``source`` desktop

**Example Response** (successful) Code: 200

.. code:: json

   {
       "cookie": {
           "itchio": "redacted"
       },
       "key": {
           "created_at": "1970-01-01T00:00:00.000000000Z",
           "id": 1234,
           "key": "API_KEY",
           "last_used_at": "1970-01-01T00:00:00.000000000Z",
           "revoked": false,
           "source": "desktop",
           "source_version": "25.5.1",
           "updated_at": "1970-01-01T00:00:00.000000000Z",
           "user_id": 7890
       },
       "success": true
   }

**Example Response** (:ref:`Needs 2FA<2 Factor Authentication>`) Code: 200

.. code:: json

   {
       "success": false,
       "token": "redacted",
       "totp_needed": true
   }

**Example Response** (failed) Code: 400

.. code:: json

   {
       "errors": [
           "Incorrect username or password"
       ]
   }

2 Factor Authentication
"""""""""""""""""""""""

* POST ``https://api.itch.io/totp/verify``
* **URL-Encoded Form**

  * ``code``  redacted (from authenticator app)
  * ``token`` redacted (from previous request)

**Example Response** (successful) Code: 200 (see response from
``/login``)

**Example Response** (failed) Code: 400

.. code:: json

   {
       "errors": [
           "invalid code"
       ]
   }

Getting the Library
^^^^^^^^^^^^^^^^^^^
* GET ``https://api.itch.io/profile/owned-keys``
* **Headers**

  * ``Authorization`` Header is API key parameters 

* **URL Parameters**

  * ``page`` an integer

.. code:: json

   {
       "per_page": 50,
       "page": 1,
       "owned_keys": [
           {
               "downloads": 31,
               "game_id": 1328853,
               "id": 69987814,
               "game": {
                   "title": "Volcanic Sinkhole Battlemap [20 x 40]",
                   "published_at": "2021-12-22T22:41:09.000000000Z",
                   "user": {
                       "cover_url": "https:\/\/img.itch.zone\/aW1nLzE4MjgzMDUucG5n\/100x100%23\/%2FTMsVq.png",
                       "url": "https:\/\/gurkenlabs.itch.io",
                       "username": "gurkenlabs",
                       "id": 475352
                   },
                   "traits": [
                       "can_be_bought"
                   ],
                   "type": "default",
                   "url": "https:\/\/gurkenlabs.itch.io\/volcanic-sinkhole-battlemap",
                   "min_price": 0,
                   "id": 1328853,
                   "short_text": "Amidst the overgrown ruins, a steaming rupture parts the earth.",
                   "created_at": "2021-12-22T22:26:43.000000000Z",
                   "classification": "assets",
                   "cover_url": "https:\/\/img.itch.zone\/aW1nLzc3Mjc1NTcucG5n\/315x250%23c\/y2h4Jk.png"
               },
               "created_at": "2022-03-08T13:41:10.000000000Z",
               "updated_at": "2022-03-08T13:41:10.000000000Z",
               "purchase_id": 9776834
           }
       ]
   }

**NB:** the final page has an empty list

Get Metadata for a game
^^^^^^^^^^^^^^^^^^^^^^^

* GET ``https://api.itch.io/games/${game_id}``
* **Headers**

  * ``Authorization`` Header is API key parameters 

* **URL Parameters**

  * ``download_key`` id from owned_keys

**Example Response** (successful) Code: 200

.. code:: json

   {
       "game": {
           "classification": "assets",
           "cover_url": "https://img.itch.zone/aW1nLzc3Mjc1NTcucG5n/315x250%23c/y2h4Jk.png",
           "created_at": "2021-12-22T22:26:43.000000000Z",
           "id": 1328853,
           "min_price": 0,
           "published_at": "2021-12-22T22:41:09.000000000Z",
           "short_text": "Amidst the overgrown ruins, a steaming rupture parts the earth.",
           "title": "Volcanic Sinkhole Battlemap [20 x 40]",
           "traits": [
               "can_be_bought"
           ],
           "type": "default",
           "url": "https://gurkenlabs.itch.io/volcanic-sinkhole-battlemap",
           "user": {
               "cover_url": "https://img.itch.zone/aW1nLzE4MjgzMDUucG5n/100x100%23/%2FTMsVq.png",
               "id": 475352,
               "url": "https://gurkenlabs.itch.io",
               "username": "gurkenlabs"
           }
       }
   }

Get Downloadable Items
^^^^^^^^^^^^^^^^^^^^^^

* GET ``https://api.itch.io/games/${game_id}/uploads``
* **Headers**

  * ``Authorization`` Header is API key parameters 

* **URL Parameters**

  * ``download_key`` id from owned_keys

**Example Response** (successful) Code: 200

.. code:: json

   {
       "uploads": [
           {
               "created_at": "2021-12-22T22:26:44.000000000Z",
               "filename": "volcanicSinkhole.dungeondraft_map",
               "game_id": 1328853,
               "id": 4976926,
               "md5_hash": "fe57c84f590189f0e57866cca3df3d26",
               "position": 0,
               "size": 712633,
               "storage": "hosted",
               "traits": {},
               "type": "default",
               "updated_at": "2022-04-13T00:28:49.000000000Z"
           }
       ]
   }

Downloading an Item
^^^^^^^^^^^^^^^^^^^

* GET ``https://api.itch.io/uploads/${id}/download``
* **URL Parameters**

  * ``api_key``
  * ``download_key_id``
  * ``uuid``

**Example Response** (successful) Code: 302 A URL to download the file

**Example Response** (invalid authentication) 401

.. code:: json

   {
       "errors":[
           "authentication required"
           ]
   }
