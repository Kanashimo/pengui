#!/usr/bin/env bash
set -e

DIR="${2##*/}"

cd ..
mkdir -p "$1/$DIR"
cp "$2/$3" "$1/$DIR"
touch "$1/$DIR.$3.generated"
