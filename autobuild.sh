#!/bin/bash

PROJECT_DIR="$(dirname "$0")"
BUILD_DIR="$PROJECT_DIR/build"

mkdir -p "$BUILD_DIR"

~/vcpkg/vcpkg install

cmake -S "$PROJECT_DIR" -B "$BUILD_DIR" -DCMAKE_TOOLCHAIN_FILE=~/vcpkg/scripts/buildsystems/vcpkg.cmake

cmake --build "$BUILD_DIR" --config Release

echo "$BUILD_DIR/weather_forecast"