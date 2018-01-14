#! /bin/bash
# Copyright 2018 the Tectonic Project
# Licensed under the MIT License

# Tear down the builder container.

if [ ! -f .ttfb_container_id ] ; then
    echo "No builder container seems to exist."
else
    cont_name=$(cat .ttfb_container_id)
    docker stop $cont_name
    docker rm $cont_name
    rm -f .ttfb_container_id
fi
