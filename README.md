# Jadeitite

Jadeitite is multifunctional and multiplatform for graphical and non-graphical application framework
written in C99 for windows and UNIX like operating systems.

Compatible with 64-bit and also 32-bit OS

## How to use it

### Examples

All examples are location in [examples](examples) folder.

- [Basic GL example](examples/main.c)
- [Asset preparation](examples/prepare.c)

### GUI

To use jadeitite gui like [jadeitite_gl](src/jadeitite_gl.h) it's necessary to use 
[jadeitite_ep.c](src/jadeitite_ep.c) as our main entrypoint.

You can also inspire by our [CMake build script](CMakeLists.txt).

## Doom Emacs Yay

[Doom emacs CC Lang Documentation](https://docs.doomemacs.org/v21.12/modules/lang/cc/)

Project compile DB:

```markdown
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE=Debug .
```
