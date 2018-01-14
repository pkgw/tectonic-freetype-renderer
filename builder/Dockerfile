FROM trzeci/emscripten-slim
LABEL maintainer="peter@newton.cx"

# Here we cargo-cult a bit from the trzeci/emscripten Dockerfile

RUN apt-get -qq -y update \
 && apt-get -qq install -y --no-install-recommends \
        autoconf \
        build-essential \
        ca-certificates \
        make \
 && emcc --clear-cache --clear-ports \
 && $EMSCRIPTEN/embuilder.py build ALL \
 && rm -rf $EM_PORTS $EM_CACHE/asmjs/ports-builds \
 && rm -rf /var/lib/apt/lists/* /var/cache/debconf/*-old
