# Tectonic’s hacked and forked FreeType font renderer

In order for [Tectonic](https://tectonic-typesetting.github.io/) to draw
precision typography on Web platforms, it needs to render glyphs from various
font files directly in the browser. This repository enables this with a hacked
version of [FreeType](https://www.freetype.org/).

In particular, this repository is a fork of FreeType that has been modified to
compile to a [WebAssembly](http://webassembly.org/) library using
[Emscripten](https://emscripten.org/). It provides a specialized API targeted
for Tectonic’s use case.

The changes from upstream FreeType are minimal, but of course this repository
has no official associated with FreeType.


## Building

For simplicity and reproducibility, the Web-executable build is created inside
a [Docker](https://www.docker.com/community-edition) container. The first step
is to create the builder image, which is derived from
[trzeci/emscripten-slim](https://hub.docker.com/r/trzeci/emscripten-slim/).
You can do this by running:

```
./tt-create-builder.sh
```

which will generate an image named `ttfontbuilder:latest`.

Next, initialize a container that will build the source:

```
./tt-configure.sh
```

Finally, to actually build the outputs, run:

```
./tt-build.sh
```

The `tt-build.sh` command can be run repeatedly and will rebuild the outputs
as you edit the source.

The builder container can be destroyed by running:

```
./tt-teardown.sh
```


## Updating

This fork derives from the upstream FreeType git repository:

```
git://git.sv.nongnu.org/freetype/freetype2.git
```

It currently derives from the 2.9 release, tag `VER-2-9`. Git can show you the
list of commits made in this fork relative to upstream:

```
git log VER-2-9..HEAD
```

The intention is to merge in updates to the underlying codebase as upstream
releases are made.


## License and copyright

The bulk of the code in this repository belongs to the FreeType project and is
licensed as described in [docs/LICENSE.TXT](docs/LICENSE.TXT). Tectonic’s
modifications are licensed under [the MIT License](LICENSE-MIT).
