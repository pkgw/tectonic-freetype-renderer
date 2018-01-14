#! /bin/bash
# Copyright 2018 the Tectonic Project
# Licensed under the MIT License

set -e

if [ ! -f .ttfb_container_id ] ; then
    docker run -d \
           -v $(pwd):/src:rw,Z \
           -e HOST_UID=$(id -u) \
           -e HOST_GID=$(id -g) \
           ttfontbuilder:latest tail -f /dev/null >.ttfb_container_id
fi

cont_name=$(cat .ttfb_container_id)

set +e
is_running=$(docker inspect --format="{{ .State.Running }}" $cont_name 2>/dev/null)
ec=$?
set -e

if [ "$is_running" != "true" ] ; then
    docker start $cont_name
fi

docker exec $cont_name bash -c "./autogen.sh \
  && emconfigure ./configure \
  && chown -R \$HOST_UID:\$HOST_GID ."
