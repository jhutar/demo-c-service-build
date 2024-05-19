Demo repo
=========

Source code
-----------

When `server.c` is compiled and started, it acts as a HTTP server serving "Hello world" response on `http://localhost:8080/`.

To compile it: `gcc server.c -o server -lpthread`

To run it: `./server`

Building in container
---------------------

First create container we will use to run the build in it:

    podman build -t mybuilder -f Containerfile .

Now use the container and run a build in it:

    rm -f server
    podman run -ti -v $(pwd):/app:z mybuilder gcc server.c -o server -lpthread

Deploy with Ansible
-------------------

WARNING: This was not tested.

Having inventory file like `inventory.ini`, you can deploy the "server" service to staging server like this:

    ansible-playbook -i inventory.ini --limit stage deploy.yaml
