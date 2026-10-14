#!/usr/bin/env bash
set -e

DIR="${2##*/}"

mkdir -p "$1/$DIR"
cp "$2/$3" "$1/$DIR"
