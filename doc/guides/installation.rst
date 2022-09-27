Installation Guide
==================

This guide is aimed at users to get themselves up and running as quickly as possible.

Linux (via Docker)
******************

* `Install Docker <https://docs.docker.com/desktop/install/linux-install/>`_
* `Install Docker Compose <https://docs.docker.com/compose/install/linux/>`_

This is currently the best way to use the program. The docker image is ``ghcr.io/theartfulbodger/thing-downloader:main``. I reccommend creating via docker-compose to enable easy control of the containers.

In an empty directory, create the file ``docker-compose.yml`` with the following contents

.. code-block:: yaml

    services:
      thing-downloader:
        image: ghcr.io/theartfulbodger/thing-downloader:main
        ports:
          - 8080:8080
        volumes:
          - .:/data

Now you can run ``$ docker-compose up -d`` in the directory to pull the image and start the container.

You can access the web panel on `http://localhost:8080 <http://localhost:8080>`_

Linux (Native)
**************

To use natively on linux, you'll need to build from source via `CMake <https://cmake.org>`_. Typical install commands:

.. code-block:: bash

    mkdir _build
    cd _build
    cmake .. -DCMAKE_INSTALL_PREFIX=/usr/local
    make -j$(nproc)
    sudo make install
    cd ../frontend
    yarn; yarn build
    sudo mkdir /usr/local/td
    sudo cp -r public /usr/local/td/frontend


Windows
*******

Not currently supported, as it relies on a couple of UNIX-isms (dlopen and popen) at present. If you're interested in porting it to Windows, please open an issue or a pull request.