#! /bin/bash
# Copyright 2018 the Tectonic Project
# Licensed under the MIT License

set -e

if [ ! -f .ttfb_container_id ] ; then
    echo >&2 "error: builder container not created; run ./tt-configure.sh first"
    exit 1
fi

cont_name=$(cat .ttfb_container_id)

set +e
is_running=$(docker inspect --format="{{ .State.Running }}" $cont_name 2>/dev/null)
ec=$?
set -e

if [ "$is_running" != "true" ] ; then
    docker start $cont_name
fi

docker exec $cont_name bash -c "emmake make && chown -R \$HOST_UID:\$HOST_GID ."
