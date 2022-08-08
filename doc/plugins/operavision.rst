Opera Vision downloader
=======================

This plugin downloads performances from `Opera Vision`_. Use of ``yt-dlp`` over standard ``youtube-dl`` is preffered as it is much faster.

.. list-table::

 * - **Name**
   - Opera Vision
 * - **Description**
   - Download performances from OperaVision.eu
 * - **Key**
   - operavision
 * - **Required Configurations**
   - ``YOUTUBE_DL_PATH`` - Path to ``yt-dlp`` or ``youtube-dl``
 * - **Required Secrets**
   - None

How it works
------------

Get Jobs Stage
^^^^^^^^^^^^^^

The script loads the `performances page`_ and scrapes each performances in the ``.newsItem`` class, adding both a video :ref:`download job<Download Jobs>` and a :ref:`metadata parsing<NFO Creator>` job.


Download Jobs
^^^^^^^^^^^^^

Video Downloader
""""""""""""""""
This contains a good starting point wrapper for ``youtube-dl`` using ``popen()`` and parsing the output with regular expressions to get the progress.

NFO Creator
"""""""""""
This scrapes the content of an individual performance page to generate an `NFO File`_ using the content.

-   **Unique ID** Video id for youtube id
-   **Title** Title of the opera (taken from the get jobs stage)
-   **Outline** Content of ``p.intro``, the introductory paragraph
-   **Plot** Paragraphs following outline.
-   **Cast** Content of ``.castTable`` tables
-   **Time** The date of the stream/premiere on youtube.

There are other fields to populate

.. _`Opera Vision`: https://operavision.eu/
.. _`performances page`: https://operavision.eu/performances
.. _`NFO File`: https://kodi.wiki/view/NFO_files