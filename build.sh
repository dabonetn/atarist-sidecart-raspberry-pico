#!/bin/bash

# Install SDK needed for building
git submodule init
git submodule update --init --recursive

# Set the environment variables of the SDKs
export FATFS_SDK_PATH=$PWD/fatfs-sdk
export PICO_SDK_PATH=$PWD/pico-sdk

# Read the release version from the version.txt file
export RELEASE_VERSION=$(cat version.txt | tr -d '\r\n ')
echo "Release version: $RELEASE_VERSION"

# Get the release date and time from the current date
export RELEASE_DATE=$(date +"%Y-%m-%d %H:%M:%S")
echo "Release date: $RELEASE_DATE"

# Set the board type to be used for building
# If nothing passed as first argument, use pico w
export BOARD_TYPE=${1:-pico_w}
echo "Board type: $BOARD_TYPE"

# Set the build directory. Delete previous contents if any
rm -rf build
mkdir build

# We assume that the last firmware was built for the same board type
# And previously pushed to the repo version

# Build the project
cd build
cmake ../romemul
make -j4

# Copy the built firmware to the /dist folder
cd ..
mkdir -p dist
cp build/romemul.uf2 dist/romemul-$BOARD_TYPE.uf2
