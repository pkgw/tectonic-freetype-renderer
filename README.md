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


## License and copyright

The bulk of the code in this repository belongs to the FreeType project and is
licensed as described in [docs/LICENSE.TXT](docs/LICENSE.TXT). Tectonic’s
modifications are licensed under [the MIT License](LICENSE-MIT).
