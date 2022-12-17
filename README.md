# Jadeitite

Jadeitite is multifunctional and multiplatform for graphical and non-graphical application framework
written in C99 for windows and UNIX like operating systems.

Compatible with 64-bit and also 32-bit OS

## Compiler support

- GCC
- TCC
- CLang

## Compiling

For compiling jadeitite with examples can be used multiple method:

- Install dependencies on your machine, e.g. SDL2 and then compile it with cmake.
- Use conan package manager [Conan Docs](https://conan.io)
  - Firstly run automation [conan.sh](conan.sh) which will setup conan for builds.
  - Then use CMake with command `-DCMAKE_CONAN_ENABLED:BOOL=ON` for enabling conan package manager.

For compiling full projects with examples will be needed to install conan package manager which will automatically 
download/install all dependencies for projects.
