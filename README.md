# Baby Raycaster

This is a barebones raycaster in C++.

## Reference
https://raytracing.github.io/books/RayTracingInOneWeekend.html#overview.

## Build Instructions

To build the project, run:

```sh
make
```

This will compile the source code and output the binary to `bin/main`.

For an optimized production build, run:

```sh
make build-prod
```

## Render Output

To build and render a single image in one command, run:

```sh
make render
```

The output .ppm image file will be written to `renders/render.ppm`.

## Other Commands

- `make clear` - Clean all build artifacts (removes `bin/` and `renders/`)
- `make build-dev` - Build with debug symbols (same as `make`)
- `make build-prod` - Build with optimizations and no debug symbols

## Dependencies
- C++14 compiler (e.g., clang++ or g++)
- Make (for build system)