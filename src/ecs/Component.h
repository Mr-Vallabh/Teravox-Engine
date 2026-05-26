#ifndef TERAVOX_COMPONENT_H
#define TERAVOX_COMPONENT_H

#include "../core/types.h"
#include "../core/tv_math.h"

// ─────────────────────────────────────────
// Mesh building blocks
// ─────────────────────────────────────────

typedef struct{
    Vec3 position;
    Vec3 normal;
    float u,v;
}Vertex;

typedef struct{
    int v1,v2;
}Edge;

typedef struct{
    int v1,v2,v3;
}Triangle;

// ─────────────────────────────────────────
// TransformComponent
// ─────────────────────────────────────────

typedef struct{
    Vec3 position;  // world position
    Vec3 rotation;  // eular angles in degrees
    Vec3 scale;     // scale per axis
}TransformComponent;

// ─────────────────────────────────────────
// MeshComponent
// ─────────────────────────────────────────

typedef struct{
    Vertex* vertices;
    Triangle* triangles;
    int     vertexCount;
    int     triangleCount;
    PrimitiveType type;
    int     isVisible;
}MeshComponent;

// ─────────────────────────────────────────
// MaterialComponent
// ─────────────────────────────────────────

typedef struct{
    Vec3 color;         //RGB float 0.0 to 1.0
    float roughness;    // 0.0 smooth and 1.0 rough
    float metallic;     //0.0 plastic and 1.0 metal
    int wireframe;      // 1 = draw wireframe
}MaterialComponent;

// ─────────────────────────────────────────
// TagComponent
// ─────────────────────────────────────────

typedef struct{
    char name[64];
    int  isSelected;
    int  isHidden;
}TagComponent;

// ─────────────────────────────────────────
// HierarchyComponent
// ─────────────────────────────────────────

typedef struct{
    EntityID parent;
    EntityID firstChild;
    EntityID nextSibling;
}HierarchyComponent;

#endif // TERAVOX_COMPONENT_H