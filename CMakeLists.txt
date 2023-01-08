cmake_minimum_required(VERSION 3.15)
project(jadeitite_framework C)
set(CMAKE_C_STANDARD 99)

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

# Libraries

## Static

add_library(jadeitite_static STATIC src/jadeitite_ep.c)
target_include_directories(jadeitite_static PUBLIC src)
target_link_libraries(jadeitite_static PUBLIC GL GLU glut m)
set_target_properties(jadeitite_static PROPERTIES LINKER_LANGUAGE C)

## Dynamic

add_library(jadeitite_shared SHARED src/jadeitite_ep.c)
target_include_directories(jadeitite_shared PUBLIC src)
target_link_libraries(jadeitite_shared PUBLIC GL GLU glut m)
set_target_properties(jadeitite_shared PROPERTIES LINKER_LANGUAGE C)

# Examples

add_executable(jadeitite_gl examples/main.c)
target_include_directories(jadeitite_gl PRIVATE src)
target_link_libraries(jadeitite_gl PRIVATE jadeitite_shared)

add_executable(jadeitite_asset examples/prepare.c)
target_include_directories(jadeitite_asset PRIVATE src vendors)
