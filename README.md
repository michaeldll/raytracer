# Baby Raycaster

This is a barebones raycaster in C++.

## Reference
https://raytracing.github.io/books/RayTracingInOneWeekend.html#overview.

## Build Instructions

To build the project with `clang`, run:

```sh
./scripts/osxBuild.sh
```

This will compile the source code and output the binary to `build/main`.

## Render Output

To render a single image, run:

```sh
./scripts/render.sh
```

The output .ppm image file will be written to `output/render.ppm`.

## Dependencies
- C++14 compiler (e.g., clang++)
- Bash shell (for running scripts)