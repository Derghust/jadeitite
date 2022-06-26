# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

## [0.2.1] - 2022-06-26 - @damien.clement
### Fixed
- Fix drawing only half circle to full drawn circle

## [0.2.0] - 2022-06-19 - @damien.clement
### Added
- Memory management
- Create static library
- Create `return_status_e` for return status
- New datatypes `byte`, `word` and `dword`
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
