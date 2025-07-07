#!/bin/bash
# Builds for OS X with clang
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$SCRIPT_DIR/.."

clang++ -std=gnu++14 -fcolor-diagnostics -fansi-escape-codes -g "$PROJECT_ROOT/src/main.cpp" -o "$PROJECT_ROOT/build/main"