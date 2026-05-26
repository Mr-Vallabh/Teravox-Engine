#include "world.h"
#include <string.h>

// everything goes here 

//init and shutdown

void world_init(World * w){
    
    // set all alive flags to 0
    memset(w->alive,0,sizeof(w->alive));

    // set all component flags to 0
    memset(w->hasTransform,0,sizeof(w->hasTransform));

    // set all Mesh flags to 0
    memset(w->hasMesh,0,sizeof(w->hasMesh));

    // set all Hierarchy flags to 0
    memset(w->hasHierarchy,0,sizeof(w->hasHierarchy));

    // set all material flags to 0
    memset(w->hasMaterial,0,sizeof(w->hasMaterial));

    // set all tags to 0
    memset(w->hasTag,0,sizeof(w->hasTag));

    
}