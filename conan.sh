#!/bin/bash

DIR_CLION_DEBUG=cmake-build-debug
DIR_CLION_RELEASE=cmake-build-release

if ! [ -d "$DIR_CLION_DEBUG" ];
then
  mkdir "$DIR_CLION_DEBUG"
fi
cd "$DIR_CLION_DEBUG"
conan install .. -s build_type=Debug --build missing
cd ../

if ! [ -d "$DIR_CLION_RELEASE" ];
then
  mkdir "$DIR_CLION_RELEASE"
fi
cd "$DIR_CLION_RELEASE"
conan install .. -s build_type=Release --build missing
cd ../

echo "DONE."
