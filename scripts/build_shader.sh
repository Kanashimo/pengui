#!/usr/bin/env bash
set -e

INPUT="$1"
OUTPUT="$2"

echo $INPUT
echo $OUTPUT

namespace="${OUTPUT%%_*}"
shader="${OUTPUT#*_}"
shader="${shader%.h}"

{
    echo "#include <string>"
    echo "namespace Shaders {"
    echo "namespace $namespace {"
    echo "inline const std::string $shader = R\"("
    cat "$INPUT"
    echo ")\";}}"
} > "$OUTPUT"
