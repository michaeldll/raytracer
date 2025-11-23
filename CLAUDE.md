# CLAUDE.md - AI Assistant Guide for Baby Raycaster

This document provides a comprehensive guide for AI assistants working with this C++ raytracer codebase.

## Project Overview

**Baby Raycaster** is a minimalist raytracer implementation in C++ following the "Ray Tracing in One Weekend" tutorial (https://raytracing.github.io/books/RayTracingInOneWeekend.html).

### Purpose
- Educational raytracing implementation
- Demonstrates fundamental raytracing concepts (ray-sphere intersection, surface normals, simple shading)
- Outputs PPM image format

### Current State
- ✅ Basic ray-sphere intersection
- ✅ Multiple object rendering (spheres)
- ✅ Surface normal visualization
- ✅ Sky gradient background
- 🚧 Camera class (WIP - stub implementation exists but not actively used)
- ❌ Materials/reflections (not yet implemented)
- ❌ Antialiasing (not yet implemented)

---

## Codebase Structure

```
raytracer/
├── src/                    # All source code (header-only except main.cpp)
│   ├── main.cpp           # Entry point and rendering loop
│   ├── common.h           # Common includes, constants, utility functions
│   ├── Vector3.h          # 3D vector class with operators
│   ├── Color.h            # Color type alias and PPM output
│   ├── Ray.h              # Ray representation (origin + direction)
│   ├── Hittable.h         # Abstract hit interface + HitRecord
│   ├── HittableList.h     # Collection of hittable objects
│   ├── Sphere.h           # Sphere primitive implementation
│   └── Camera.h           # Camera class (WIP, not fully integrated)
├── bin/                   # Build output directory (gitignored)
├── renders/               # Rendered images output (gitignored)
├── .vscode/               # VSCode configuration
│   ├── tasks.json        # Build tasks for VSCode
│   └── settings.json     # C++ file associations
├── Makefile              # Primary build system
├── README.md             # User-facing documentation
└── .gitignore            # Excludes bin/, renders/, .vscode, .DS_STORE
```

---

## Architecture & Design Patterns

### Object-Oriented Design
- **Polymorphism**: `Hittable` abstract base class with virtual `hit()` method
- **Inheritance**: `Sphere` and `HittableList` inherit from `Hittable`
- **Composition**: `HittableList` contains vector of `shared_ptr<Hittable>`

### Header-Only Structure
- All classes except `main.cpp` are header-only (no `.cpp` implementations)
- Inline functions used extensively to avoid linker issues
- `common.h` serves as the precompiled header gathering dependencies

### Data Flow
1. **Setup** (main.cpp:52-86): Configure image dimensions, viewport, camera
2. **Scene Construction** (main.cpp:64-67): Add objects to `HittableList`
3. **Rendering Loop** (main.cpp:91-105):
   - For each pixel (y, x)
   - Calculate ray from camera through pixel center
   - Call `getRayColor()` to trace ray through scene
   - Write color to stdout in PPM format
4. **Ray Tracing** (main.cpp:40-50):
   - Check if ray hits any object via `scene.hit()`
   - If hit: shade using surface normal (50% normal color + 50% white)
   - If miss: return sky gradient background

---

## Key Components

### Vector3 (`Vector3.h`)
**Purpose**: 3D vector math (positions, directions, colors)

**Key Methods**:
- `x()`, `y()`, `z()`: Component accessors
- `length()`, `lengthSquared()`: Magnitude calculations
- Operators: `+`, `-`, `*`, `/`, `+=`, `*=`, `/=`
- Utility functions: `dot()`, `cross()`, `normalize()`

**Usage Pattern**:
```cpp
Vector3 v1(1.0, 2.0, 3.0);
Vector3 v2(4.0, 5.0, 6.0);
double dotProduct = dot(v1, v2);
Vector3 normalized = normalize(v1);
```

### Ray (`Ray.h`)
**Purpose**: Represents a ray with origin and direction

**Structure**:
- Private: `originPoint`, `directionVector`
- `at(t)`: Returns point along ray at parameter t: `origin + t * direction`

### Hittable (`Hittable.h`)
**Purpose**: Abstract interface for ray-intersectable objects

**HitRecord Structure**:
- `position`: Hit point in 3D space
- `normal`: Surface normal at hit point (always faces against ray)
- `t`: Ray parameter at hit point
- `frontFace`: Whether ray hit front face
- `setFaceNormal()`: Ensures normal always opposes ray direction

**Interface**:
```cpp
virtual bool hit(const Ray &ray, double rayTMin, double rayTMax, HitRecord &record) const = 0;
```

### Sphere (`Sphere.h`)
**Purpose**: Sphere primitive with ray intersection

**Algorithm** (lines 13-31):
- Solves quadratic equation for ray-sphere intersection
- Uses geometric formulation with `h = dot(d, oc)` optimization
- Returns nearest valid intersection in [rayTMin, rayTMax] range
- Handles both front-face and back-face intersections

### HittableList (`HittableList.h`)
**Purpose**: Scene graph (collection of objects)

**Implementation**:
- `std::vector<shared_ptr<Hittable>> objects`
- `hit()`: Iterates all objects, returns closest intersection
- Uses `shared_ptr` for automatic memory management

### Color (`Color.h`)
**Purpose**: Type alias for Vector3 + PPM output

**writeColor()**: Converts [0,1] float RGB to [0,255] byte range for PPM format

---

## Build System

### Makefile Targets

| Target | Description | Flags |
|--------|-------------|-------|
| `make` or `make build` | Build debug binary | `-O0 -ggdb` |
| `make build-dev` | Explicit debug build | `-O0 -ggdb` |
| `make build-prod` | Optimized release build | `-O2` (no debug symbols) |
| `make render` | Build + render to `renders/render.ppm` | Runs binary, redirects stdout |
| `make clear` | Clean build artifacts | Removes `bin/` and `renders/` |

### Compiler Settings
- **Compiler**: `clang++` (can override with `CXX=g++ make`)
- **Standard**: C++14
- **Include Path**: `-I./src` (all headers accessible without path)
- **Warnings**: `-Wall -Wextra -Wpedantic`
- **Optimization**: `-march=native` (CPU-specific optimizations)

### Build Output
- **Binary**: `bin/main`
- **Render**: `renders/render.ppm` (PPM image format)

### Dependencies
- C++14 compatible compiler (clang++ or g++)
- Standard library only (no external dependencies)
- Bash shell (for Makefile)

---

## Development Workflow

### Making Changes

1. **Modify source files** in `src/`
2. **Rebuild**: `make` (or `make build-dev`)
3. **Test render**: `make render`
4. **View output**: Open `renders/render.ppm` in image viewer

### Common Workflows

**Add a new primitive type**:
1. Create `src/NewPrimitive.h`
2. Inherit from `Hittable`
3. Implement `hit()` method
4. Add to scene in `main.cpp` via `scene.add(make_shared<NewPrimitive>(...))`

**Modify rendering parameters**:
- Image size: `main.cpp:54-56` (ASPECT_RATIO, IMAGE_WIDTH, IMAGE_HEIGHT)
- Camera/viewport: `main.cpp:70-85`
- Scene objects: `main.cpp:64-67`

**Change shading**:
- Modify `getRayColor()` in `main.cpp:40-50`
- Current: Normal visualization (maps normals to RGB)

### VSCode Integration

**Build Task**: Press `Ctrl+Shift+B` (or `Cmd+Shift+B` on Mac)
- Runs clang on active file (configured in `.vscode/tasks.json`)
- Note: Use Makefile for full project builds

**C++ IntelliSense**: Configured via `.vscode/settings.json`
- All standard library headers have file associations

---

## Code Conventions

### Naming Conventions
- **Classes**: PascalCase (`Vector3`, `HittableList`, `Ray`)
- **Functions**: camelCase (`hitSphere`, `getRayColor`, `writeColor`)
- **Variables**: camelCase (`pixelColor`, `rayDirection`)
- **Constants**: SCREAMING_SNAKE_CASE (`ASPECT_RATIO`, `IMAGE_WIDTH`, `FOCAL_LENGTH`)
- **Members**: camelCase with descriptive names (`originPoint`, `directionVector`)

### Code Style
- **Includes**: Group by category (C++ std, project headers)
- **Braces**: Opening brace on same line for functions, next line for control flow
- **Indentation**: Spaces (4 spaces per tab)
- **Const-correctness**: Use `const` for read-only parameters and methods
- **Auto**: Used sparingly for obvious types

### Header Guards
Standard `#ifndef` pattern:
```cpp
#ifndef FILENAME_H
#define FILENAME_H
// ... content ...
#endif
```

### Memory Management
- Use `shared_ptr` for heap-allocated objects
- Use `make_shared` for construction
- Stack allocation preferred for temporary objects

---

## Mathematical Foundations

### Coordinate System
- **X**: Right
- **Y**: Up
- **Z**: Out of screen (negative Z is into scene)
- Right-handed coordinate system

### Ray Equation
`P(t) = Origin + t * Direction`
- `t`: Ray parameter (distance along ray)
- Valid range typically: [0, infinity] or [tMin, tMax]

### Sphere Intersection
Geometric formulation (optimized):
```
oc = center - origin
a = dot(direction, direction)
h = dot(direction, oc)
c = dot(oc, oc) - radius²
discriminant = h² - a*c

if discriminant < 0: no hit
else: t = (h ± sqrt(discriminant)) / a
```

### Normal Calculation
For sphere: `normal = normalize(hitPoint - center)`
- Always unit length
- Points outward from surface
- `setFaceNormal()` flips if needed to oppose ray

---

## Current Issues & WIP

### Camera Class (WIP)
- File: `src/Camera.h:1-13`
- Status: Stub implementation exists but not integrated
- Current: Camera logic inlined in `main.cpp:70-85`
- Future: Refactor camera setup into Camera class

### Code Duplication
- `hitSphere()` in `main.cpp:7-23` duplicates logic from `Sphere::hit()`
- Status: Legacy code, not actively used (scene uses `Sphere::hit()`)
- Recommendation: Remove `hitSphere()` and `getSphereNormal()` helper functions

### README vs Makefile Discrepancy
- README mentions `./scripts/clangBuild.sh` and `./scripts/render.sh`
- Reality: No `scripts/` directory exists, use Makefile instead
- Recommendation: Update README to reference Makefile targets

---

## AI Assistant Guidelines

### When Modifying Code

1. **Read before writing**: Always read existing files before suggesting modifications
2. **Maintain consistency**: Follow existing naming conventions and code style
3. **Preserve header-only structure**: Keep implementations in headers except for main.cpp
4. **Test after changes**: Suggest running `make render` to verify changes
5. **Update documentation**: If changing architecture, update this CLAUDE.md

### Common Pitfall Prevention

❌ **Don't** create `.cpp` implementation files (violates header-only structure)
❌ **Don't** modify `common.h` without understanding include dependencies
❌ **Don't** assume scripts directory exists (use Makefile instead)
❌ **Don't** forget to include header guards in new headers
❌ **Don't** use raw pointers (use `shared_ptr` for heap objects)

✅ **Do** add new primitives as header-only classes inheriting Hittable
✅ **Do** use `make render` workflow for testing
✅ **Do** maintain const-correctness
✅ **Do** use inline functions in headers to avoid linker errors
✅ **Do** leverage Vector3 operators for readable math

### Debugging Tips

**Build errors**:
- Check include order (common.h should gather dependencies)
- Verify header guards
- Ensure all inline keyword for multi-definition functions

**Runtime issues**:
- Verify ray parameter ranges (tMin, tMax)
- Check for division by zero in ray-sphere intersection
- Ensure normals are unit length

**Image artifacts**:
- Black pixels: Ray missed all objects and background
- Incorrect colors: Check color component range [0, 1]
- Banding: Precision issues in color conversion to [0, 255]

### Suggested Improvements (for reference)

If user requests enhancements, consider:
1. **Antialiasing**: Add multiple samples per pixel with random jitter
2. **Materials**: Add Lambertian, metal, dielectric materials
3. **Camera class**: Refactor camera logic from main.cpp into Camera.h
4. **Positionable camera**: Add camera positioning and look-at
5. **Depth of field**: Add defocus blur
6. **Performance**: Parallelize pixel loop with OpenMP/threads

---

## Git Workflow

### Commit Message Convention
This project uses **Gitmoji** for commit messages:
- `:sparkles:` - New feature
- `:bug:` - Bug fix
- `:recycle:` - Refactoring
- `:construction:` - Work in progress
- `:hammer:` - Build/tooling changes
- `:memo:` - Documentation
- `:fire:` - Removing code/files
- `:tada:` - Initial commit

Example: `:sparkles: Add anti-aliasing support`

### Current Branch
Development occurs on feature branches prefixed with `claude/`

---

## Quick Reference

### File Modification Impact Map
| File | Affects | Rebuild Required |
|------|---------|------------------|
| `main.cpp` | Rendering logic, scene setup | Yes |
| `Vector3.h` | All math operations | Yes (recompile all) |
| `Sphere.h` | Sphere rendering | Yes |
| `Hittable*.h` | Object intersection system | Yes |
| `Camera.h` | Currently nothing (WIP) | Yes |
| `Makefile` | Build process | No (Make handles) |

### Key Constants
| Constant | Location | Value | Purpose |
|----------|----------|-------|---------|
| `infinity` | common.h:21 | `numeric_limits<double>::infinity()` | Ray max range |
| `pi` | common.h:22 | 3.141592653589793 | Mathematical constant |
| `ASPECT_RATIO` | main.cpp:54 | 1.0 | Image aspect ratio |
| `IMAGE_WIDTH` | main.cpp:55 | 400 | Output image width |
| `FOCAL_LENGTH` | main.cpp:70 | 1.0 | Camera focal length |
| `VIEWPORT_HEIGHT` | main.cpp:71 | 2.0 | Viewport height |

### Common Operations
```bash
# Build debug version
make

# Build optimized version
make build-prod

# Render image
make render

# Clean all build artifacts
make clear

# View output image (example with ImageMagick)
display renders/render.ppm

# Convert PPM to PNG (example)
convert renders/render.ppm renders/render.png
```

---

## Additional Resources

- **Tutorial**: https://raytracing.github.io/books/RayTracingInOneWeekend.html
- **PPM Format**: http://netpbm.sourceforge.net/doc/ppm.html
- **Ray Tracing Gems**: https://www.realtimerendering.com/raytracinggems/

---

**Last Updated**: 2025-11-23
**Document Version**: 1.0
**Codebase Commit**: `ab91e39` (:construction: Add WIP Camera)
