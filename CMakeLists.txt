cmake_minimum_required(VERSION 3.15)
project(jadeitite_framework C)
set(CMAKE_C_STANDARD 99)

# Conan

option(CMAKE_CONAN_ENABLED "Enabled conan integration with cmake." OFF)

IF(${CMAKE_CONAN_ENABLED})
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup(TARGETS)

    SET(PACKAGE_SDL CONAN_PKG::sdl)
ELSE()
    SET(PACKAGE_SDL SDL2)
ENDIF()


# Compiler tags

find_program(CPP_CHECK "cppcheck")
IF(CPP_CHECK)
    set(CMAKE_C_CPPCHECK "cppcheck")
ENDIF()

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    message("Debug mode is enabled")
    set(GCC_WARNINGS
            "-pedantic" "-Wall"
            "-Wno-missing-braces" "-Wextra" "-Wno-missing-field-initializers"
            "-Wformat=2"
            "-Wswitch-default" "-Wswitch-enum" "-Wcast-align" "-Wpointer-arith"
            "-Wbad-function-cast" "-Wstrict-overflow=5" "-Wstrict-prototypes" "-Winline"
            "-Wundef" "-Wnested-externs" "-Wcast-qual" "-Wshadow" "-Wunreachable-code"
            "-Wlogical-op" "-Wfloat-equal" "-Wstrict-aliasing=2" "-Wredundant-decls"
            "-Wold-style-definition"
            "-Werror"
            "-ggdb3"
            "-O0"
            "-fno-omit-frame-pointer" "-ffloat-store" "-fno-common" "-fstrict-aliasing"
            )
    set(GCC_OPTIMIZATION "-O0")
    set(GCC_LEVEL_MODE "-DLEVEL_DEBUG")
elseif (${CMAKE_BUILD_TYPE} STREQUAL "Release")
    set(GCC_OPTIMIZATION "-O3")
    set(GCC_LEVEL_MODE "-DLEVEL_RELEASE")
endif ()

# Examples

add_subdirectory(examples)
