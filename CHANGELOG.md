# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

Format: 

```markdown
## [MAJOR.MINOR.PATCH] - YYYY-MM-DD - @USER
```

## [Unreleased]

## [0.5.0] - 2023-01-08 - @damien.clement
### Changed
- Replace SDL2 for GL and glut again.
- Moved entrypoint to own `c` file due to issue with some compiler
complying with multiple main function.
- Moved GUI function to own `h` file for being able to use jadeitite
utils without gui
### Removed
- CLionstyle.

## [0.4.4] - 2022-12-19 - @damien.clement
### Added
- Added drawing for SDL2 filled rectangle.
### Changed
- Set VSync for SDL2 renderer.
### Fixed
- Removed duplicated callback `onDetach`.

## [0.4.3] - 2022-12-18 - @damien.clement
### Changed
- Change license from `GNU LESSER GENERAL PUBLIC LICENSE` to `GNU GENERAL PUBLIC LICENSE`

## [0.4.2] - 2022-12-18 - @damien.clement
### Changed
- Rename functions and values with prefix `jdt` as Jadeitite.
### Fixed
- Fixed refreshing with SDL.

## [0.4.1] - 2022-12-17 - @damien.clement
### Changed
- Implement conan for build project.
### Added
- conanfile for specifying dependencies.
- Automation script for conan cmake.

## [0.4.0] - 2022-10-29 - @damien.clement
### Changed
- Shrink all sources to single header `c` file
### Removed
- Removed OpenGl with GLUT support
  - Replaced with SDL2
- VSCode setting and c_cpp_settings

## [0.3.4] - 2022-08-27 - @damien.clement
### Changed
- Added a new jadeitite utils library from **JADEITITE_C_FILES** and later linked to other libraries
### Removed
- Moved emulator for MOS 6502 processor to its own [repository](https://git.hussite-software.com/Derghust/MOS6502)

## [0.3.3] - 2022-08-23 - @damien.clement
### Added
- Include `cppcheck` to cmake
### Fixed
- Freeing pointers before return `NULL` or error in `file.c` functions

## [0.3.2] - 2022-08-23 - @damien.clement
### Fixed
- Rename `citoa` to `int_to_str` in header `string.h`
### Added
- Added `vscode` project properties
### Changed
- Split `sdl` and `glut` from `renderer` root to each own subfolder with own
entrypoint

## [0.3.1] - 2022-07-31 - @damien.clement
### Added
- Initialize SDL2 renderer
### Changed
- Rewrite entrypoint for multiple renderer

## [0.3.0] - 2022-06-28 - @damien.clement
### Added
- Added font8x8 from https://github.com/dhepper/font8x8
- Added WIP SDL2 lib implementation
- Added file read and write implementation
### Changed
- Change static lib name from `jadeitite` to `jadeitite_glut`
- Add simple drawing for example
- Change example name for `base_template` to `glut_template`
### Fixed
- Setup macro for system config for `TCC` compiler

## [0.2.1] - 2022-06-26 - @damien.clement
### Fixed
- Fix drawing only half circle to full drawn circle

## [0.2.0] - 2022-06-19 - @damien.clement
### Added
- Memory management
- Create static library
- Create `return_status_e` for return status
- New data types `byte`, `word` and `dword`
### Changed
- Move sources to own package `jadeitite` and others `renderer`, `entrypoint`
- Remove jadeitite name from sources
- Split `entrypoint_glut` to header file c file
- Moved window structs to own header file

## [0.1.3] - 2022-06-13 - @damien.clement
### Changed
- Jadeitite header file was split into own header/c source file

## [0.1.2] - 2022-06-12 - @damien.clement
### Changed
- Move entry point to own header file
- Implement all core function as static for multiple include

## [0.1.1] - 2022-06-07 - @damien.clement
### Changed
- Refactor names for parameters from `t_*` `p_*`
- Refactor coding style
### Added
- Added CLion coding style

## [0.1.0] - 2022-06-04 - @damien.clement
### Added
- Initialize framework with basic renderer
