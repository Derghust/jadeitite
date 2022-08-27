# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

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
