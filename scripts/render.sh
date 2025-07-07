#!/bin/bash
# Renders a single image
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$SCRIPT_DIR/.."

"$PROJECT_ROOT/build/main" > "$PROJECT_ROOT/output/render.ppm"