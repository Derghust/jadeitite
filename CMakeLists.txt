cmake_minimum_required(VERSION 3.15)
project(jadeitite_framework C)

set(CMAKE_C_STANDARD 99)

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

set(
  JADEITITE_GLUT_C_FILES
  src/jadeitite/entrypoint/entrypoint_glut.c src/jadeitite/renderer/gl.c
  src/jadeitite/renderer/glut.c
)

set(
  JADEITITE_C_FILES
  src/jadeitite/memory.c src/jadeitite/math.c src/jadeitite/string.c
)

add_library(jadeitite STATIC ${JADEITITE_GLUT_C_FILES} ${JADEITITE_C_FILES})
target_include_directories(jadeitite PRIVATE src)
target_link_libraries(jadeitite PRIVATE GL GLU glut m)

add_subdirectory(examples)
