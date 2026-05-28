# Teravox Engine

> "AutoCAD builds blueprints. Teravox builds worlds."

A 3D world builder engine built from scratch in C.
No OpenGL. No game framework. Pure C + SDL2.

![License](https://img.shields.io/badge/license-MIT-blue)
![Language](https://img.shields.io/badge/language-C-orange)
![Status](https://img.shields.io/badge/status-active-green)

---

## What is Teravox?

Teravox is a real time 3D world builder engine
built entirely from scratch in C.

Every system is hand written:
- Custom math library (Vec2, Vec3, Vec4, Mat4x4)
- Perspective projection pipeline (MVP matrices)
- FPS camera with mouse look
- Scene management system
- World save and load (.tvw format)
- Ground grid renderer
- Software wireframe renderer

No OpenGL. No Unity. No Unreal.
Just C, SDL2, and first principles.

---

## Current Status — v0.1 Wireframe Engine

✓ Custom C math library     33 functions
✓ MVP matrix pipeline       perspective projection
✓ FPS camera                WASD + mouse look
✓ Cube placement            press 1
✓ Cube removal              press 2
✓ Variable cube sizes       UP/DOWN arrow keys
✓ Ground grid               spatial reference
✓ Save world                Ctrl+S → world.tvw
✓ Load world                Ctrl+L ← world.tvw
✓ Dark editor background    feels like real editor

---

## Architecture

Teravox/
│
├── src/
│   ├── core/
│   │   ├── tv_math.h        Vec2, Vec3, Vec4, Mat4x4
│   │   ├── types.h          EntityID, enums, constants
│   │   └── logger.h         TV_LOG, TV_WARN, TV_ERROR
│   │
│   ├── ecs/
│   │   ├── entity.h         Entity ID helpers
│   │   ├── component.h      Transform, Mesh, Material
│   │   └── world.h          World struct — ECS foundation
│   │
│   └── (graphics, editor, world — coming in v0.2)
│
├── main.c                   Engine entry point
├── README.md
└── Makefile

---

## Controls

| Key | Action |
|-----|--------|
| `W A S D` | Move camera |
| `Mouse` | Look around |
| `Space` | Move up |
| `Left Shift` | Move down |
| `1` | Place cube at camera position |
| `2` | Remove last placed cube |
| `UP Arrow` | Increase next cube size |
| `DOWN Arrow` | Decrease next cube size |
| `Ctrl + S` | Save world to world.tvw |
| `Ctrl + L` | Load world from world.tvw |
| `ESC` | Quit |

---

## Build and Run

### Requirements
- GCC or Clang
- SDL2 library

### Linux / Mac
```bash
gcc main.c -o teravox -lSDL2 -lm
./teravox
```

### Windows (MinGW)
```bash
gcc main.c -o teravox.exe -lSDL2 -lmingw32 -lSDL2main -lm
teravox.exe
```

---

## Roadmap

### v0.2 — Triangle Rasterizer

→ framebuffer — Uint32 pixel array
→ zbuffer — depth testing
→ filled colored triangles
→ flat shading
→ backface culling

### v0.3 — Full Editor

→ 10 primitives
cube, cuboid, sphere, cylinder
cone, pyramid, plane, capsule
torus, wedge
→ multithreaded tile renderer
→ frustum culling
→ ImGui UI panels
→ object selection — click to select
→ transform gizmos — move rotate scale

### v1.0 — World Builder

Static world octree
→ collaborative .tvw files
→ floor template system
→ terrain editing
→ basic lighting
→ OBJ import
→ undo/redo system

### v2.0 — Physics Sandbox

→ rigid body physics
→ gravity and collisions
→ simulate button
→ restore world after simulation

---

## Technical Highlights

### Custom Math Library
33 hand written functions.
Zero dependencies beyond math.h.

```c
Vec3 a = vec3(1, 0, 0);
Vec3 b = vec3(0, 1, 0);
Vec3 c = vec3_cross(a, b);  // (0, 0, 1)

Mat4x4 view = mat4_lookat(eye, target, up);
Mat4x4 proj = mat4_perspective(60.0f, aspect, 0.1f, 1000.0f);
Mat4x4 mvp  = mat4_multiply(proj, view);
```

### MVP Matrix Pipeline
Standard perspective projection.
Derived from first principles.
No OpenGL required.

vertex → model matrix → world space
→ view matrix  → camera space
→ proj matrix  → clip space
→ divide by w  → NDC space
→ viewport     → screen pixels

### Static World Octree (v1.0)
World objects are static between edits.
Octree rebuilt only on add/delete.
Read only during rendering.
Naturally thread safe.
Naturally partitions collaborative edits.

---

## Philosophy

Teravox is built on three beliefs:

**1. Understanding over abstraction**
Every system built from scratch.
No magic. No black boxes.
Every line understood completely.

**2. The artist's feeling matters**
Tools should feel like extensions of hands.
Fast. Direct. Beautiful.
The experience of building
is as important as what you build.

**3. Simple tools, complex worlds**
10 primitives can build anything.
A city. A mountain. A building.
Complexity emerges from
simple tools used creatively.

---

## Inspiration

Built studying the lineage of:
- Quake engine — John Carmack (C, software renderer)
- Handmade Hero — Casey Muratori (C, from scratch)
- id Tech 1 — pure software rendering

---

## Author

**Vallabh** — [@Mr-Vallabh](https://github.com/Mr-Vallabh)

Built from scratch. Every line. No tutorials.
Just documentation, first principles, and persistence.

---

## License

MIT License — use it, learn from it, build on it.