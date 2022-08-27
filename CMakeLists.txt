cmake_minimum_required(VERSION 3.15)
project(jadeitite_framework C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_CPPCHECK "cppcheck")

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

#============================================================================#
#                                Utils library                               #
#============================================================================#

set(
        JADEITITE_UTILS_C_FILES
        src/jadeitite/file.c src/jadeitite/math.c src/jadeitite/memory.c
        src/jadeitite/string.c
)

add_library(jadeitite_utils STATIC ${JADEITITE_UTILS_C_FILES})
target_include_directories(jadeitite_utils PRIVATE src)

#============================================================================#
#                                 GUI - GLUT                                 #
#============================================================================#

set(
        JADEITITE_GLUT_C_FILES
        src/jadeitite/renderer/glut/entrypoint.c src/jadeitite/renderer/glut/gl.c
        src/jadeitite/renderer/glut/glut.c src/jadeitite/renderer/ui.c
)

add_library(jadeitite_glut STATIC ${JADEITITE_GLUT_C_FILES})
target_include_directories(jadeitite_glut PRIVATE src)
target_link_libraries(jadeitite_glut PRIVATE GL GLU glut m jadeitite_utils)

#============================================================================#
#                                 GUI - SDL2                                 #
#============================================================================#

set(
        JADEITITE_SDL2_C_FILES
        src/jadeitite/renderer/sdl/entrypoint.c src/jadeitite/renderer/sdl/sdl2.c
)

add_library(jadeitite_sdl2 STATIC ${JADEITITE_SDL2_C_FILES})
target_include_directories(jadeitite_sdl2 PRIVATE src)
target_link_libraries(jadeitite_sdl2 PRIVATE GL GLU glut m SDL2 jadeitite_utils)

add_subdirectory(examples)
