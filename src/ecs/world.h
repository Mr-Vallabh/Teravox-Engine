#ifndef TERAVOX_WORLD_H
#define TERAVOX_WORLD_H

#include "../core/types.h"
#include "../core/logger.h"
#include "entity.h"
#include "component.h"

// everything goes here 

// ─────────────────────────────────────────
// World
// holds all entities and components
// ─────────────────────────────────────────

typedef struct {

    // ── entity alive tracking ─────────────
    int      alive[MAX_ENTITIES];
    uint32_t aliveCount;

    // ── component storage ─────────────────
    // index = EntityID
    TransformComponent  transforms[MAX_ENTITIES];
    MeshComponent       meshes[MAX_ENTITIES];
    MaterialComponent   materials[MAX_ENTITIES];
    TagComponent        tags[MAX_ENTITIES];
    HierarchyComponent  hierarchies[MAX_ENTITIES];

    // ── component flags ───────────────────
    // does this entity have this component
    int hasTransform[MAX_ENTITIES];
    int hasMesh[MAX_ENTITIES];
    int hasMaterial[MAX_ENTITIES];
    int hasTag[MAX_ENTITIES];
    int hasHierarchy[MAX_ENTITIES];

    // ── ID counters ───────────────────────
    EntityID nextPrimitive;
    EntityID nextCustom;
    EntityID nextLegend;

} World;

#endif //TERAVOX_WORLD_H