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

`make build-dev` outputs a development build with debug symbols (same as `make`).

`make build-prod` outputs a production build with optimizations and no debug symbols.

## Render Output

To build and render a single image in one command, run:

```sh
make render
```

The output .ppm image file will be written to `renders/render.ppm`.

## Other Commands

- `make clear` - Clean build and render artifacts (removes `bin/` and `renders/`)

## Dependencies

- Clang
- Make
