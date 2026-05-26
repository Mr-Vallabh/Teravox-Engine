#ifndef TERAVOX_TYPES_H
#define TERAVOX_TYPES_H

#include <stdint.h>
#include <stdbool.h>

// Everything goes here 

//1.Core ID typedefs

typedef uint32_t EntityID;
typedef uint32_t ComponentID;

//2.Null sentinels //

#define NULL_ENTITY 0
#define NULL_COMPONENT 0

//3.Engine Capacity

#define MAX_ENTITIES 1000000

//4.ID Range Constants

#define RESERVED_MIN 0
#define RESERVED_MAX 99

#define PRIMITIVE_MIN 100
#define PRIMITIVE_MAX 9999

#define CUSTOM_MIN 10000
#define CUSTOM_MAX 99999

#define LEGEND_MIN 100000
#define LEGEND_MAX 999999

//5.Entity Range enum

typedef enum{
    RANGE_RESERVED = 0,
    RANGE_PRIMITIVE = 1,
    RANGE_CUSTOM = 2,
    RANGE_LEGEND = 3
}EntityRange;

//6.PrimitiveType enum
typedef enum{
    PRIMITIVE_CUBE      = 0,
    PRIMITIVE_CUBOID    = 1,
    PRIMITIVE_SPHERE    = 2,
    PRIMITIVE_CYLINDER  = 3,
    PRIMITIVE_CONE      = 4,
    PRIMITIVE_PYRAMID   = 5,
    PRIMITIVE_PLANE     = 6,
    PRIMITIVE_CAPSULE   = 7,
    PRIMITIVE_TORUS     = 8,
    PRIMITIVE_WEDGE     = 9
}PrimitiveType;

//7.Component ID constants
#define TRANSFORM_ID    1
#define MESH_ID         2
#define MATERIAL_ID     3
#define TAG_ID          4
#define HIERARCHY_ID    5

#endif //TERAVOX_TYPES_H