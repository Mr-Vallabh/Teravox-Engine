#ifndef TERAVOX_ENTITY_H
#define TERAVOX_ENTITY_H

#include "../core/types.h"

//check if entity is valid 
static inline int entity_isValid(EntityID id){
    return id != NULL_ENTITY;
}

// check which range entity belong to
static inline int entity_isReserved(EntityID id){
    return id >= RESERVED_MIN && id <= RESERVED_MAX;
}

static inline int entity_isPrimitive(EntityID id){
    return id >= PRIMITIVE_MIN && id <= PRIMITIVE_MAX;
}

static inline int entity_isCustom(EntityID id){
    return id >= CUSTOM_MIN && id <= CUSTOM_MAX;
}

static inline int entity_isLegend(EntityID id){
    return id >= LEGEND_MIN && id <= LEGEND_MAX;
}

// get range of entity
static inline EntityRange entity_getRange(EntityID id){
    if(entity_isReserved(id))   return RANGE_RESERVED;
    if(entity_isPrimitive(id))  return RANGE_PRIMITIVE;
    if(entity_isCustom(id))     return RANGE_CUSTOM;
    if(entity_isLegend(id))     return RANGE_LEGEND;
    return RANGE_RESERVED;
}

#endif // TERAVOX_ENTITY_H