# Teravox Engine

A 3D world builder engine built from scratch in C.

## Current Status — v0.1 Wireframe
- Custom math library (Vec2, Vec3, Vec4, Mat4x4)
- Perspective projection — MVP matrix pipeline
- FPS camera — WASD + mouse look
- Place cubes — press 1
- Remove last cube — press 2
- Variable cube size — UP/DOWN arrow keys
- Ground grid
- Built with SDL2

## Controls
| Key | Action |
|-----|--------|
| WASD | Move camera |
| Mouse | Look around |
| Space | Move up |
| Left Shift | Move down |
| 1 | Place cube |
| 2 | Remove last cube |
| UP arrow | Increase cube size |
| DOWN arrow | Decrease cube size |
| ESC | Quit |

## Build
```bash
gcc main.c -o teravox -lSDL2 -lm
```

## Roadmap
- Triangle rasterization
- All 10 primitives
- Flat shading + lighting
- ImGui editor panels
- Save/load world files
- Physics sandbox