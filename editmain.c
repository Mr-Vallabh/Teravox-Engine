//This was the code given by claude originally i am going to add a new shape inside it 
// like a cuboid ok 


#include <SDL2/SDL.h>
#include <stdio.h>
#include "src/core/tv_math.h"
#include "src/core/types.h"
#include "src/core/logger.h"

#define WINDOW_WIDTH  1366
#define WINDOW_HEIGHT 768
#define MAX_VERTICES  8
#define MAX_EDGES     12
#define MAX_OBJECTS   1000
#define CURRENT_CUBE_SIZE 2.0f
#define MIN_CUBE_SIZE 0.01f
#define MAX_CUBE_SIZE 10.0f

// ─────────────────────────────────────────
// Object
// ─────────────────────────────────────────

typedef struct {
    Vec3 vertices[MAX_VERTICES];
    int  edges[MAX_EDGES][2];
    int  vertexCount;
    int  edgeCount;
    Vec3 position;
    Vec3 rotation;
    Vec3 scale;
} Object;

// ─────────────────────────────────────────
// Camera
// ─────────────────────────────────────────

typedef struct {
    Vec3  position;
    float yaw;
    float pitch;
    float speed;
    float sensitivity;
} Camera;

// ─────────────────────────────────────────
// Scene
// ─────────────────────────────────────────

typedef struct {
    Object objects[MAX_OBJECTS];
    int    count;
} Scene;

// ─────────────────────────────────────────
// Generate Cube
// ─────────────────────────────────────────

void generateCube(Object* obj, float size) {

    float h = size / 2.0f;

    obj->vertices[0] = vec3(-h, -h,  h);
    obj->vertices[1] = vec3( h, -h,  h);
    obj->vertices[2] = vec3( h, -h, -h);
    obj->vertices[3] = vec3(-h, -h, -h);
    obj->vertices[4] = vec3(-h,  h,  h);
    obj->vertices[5] = vec3( h,  h,  h);
    obj->vertices[6] = vec3( h,  h, -h);
    obj->vertices[7] = vec3(-h,  h, -h);

    obj->edges[0][0]  = 0; obj->edges[0][1]  = 1;
    obj->edges[1][0]  = 1; obj->edges[1][1]  = 2;
    obj->edges[2][0]  = 2; obj->edges[2][1]  = 3;
    obj->edges[3][0]  = 3; obj->edges[3][1]  = 0;

    obj->edges[4][0]  = 4; obj->edges[4][1]  = 5;
    obj->edges[5][0]  = 5; obj->edges[5][1]  = 6;
    obj->edges[6][0]  = 6; obj->edges[6][1]  = 7;
    obj->edges[7][0]  = 7; obj->edges[7][1]  = 4;

    obj->edges[8][0]  = 0; obj->edges[8][1]  = 4;
    obj->edges[9][0]  = 1; obj->edges[9][1]  = 5;
    obj->edges[10][0] = 2; obj->edges[10][1] = 6;
    obj->edges[11][0] = 3; obj->edges[11][1] = 7;

    obj->vertexCount = 8;
    obj->edgeCount   = 12;

    obj->position = vec3(0, 0, 0);
    obj->rotation = vec3(0, 0, 0);
    obj->scale    = vec3(1, 1, 1);
}

// ─────────────────────────────────────────
// Draw Object
// ─────────────────────────────────────────

void drawObject(SDL_Renderer* r, Object* obj, Mat4x4 mvp) {

    int screenX[MAX_VERTICES];
    int screenY[MAX_VERTICES];

    for(int i = 0; i < obj->vertexCount; i++) {

        Vec4 v = vec4(
            obj->vertices[i].x,
            obj->vertices[i].y,
            obj->vertices[i].z,
            1.0f
        );

        Vec4 clip = mat4_multiply_vec4(mvp, v);

        // skip vertices behind camera
        if(clip.w <= 0.0f) {
            screenX[i] = -9999;
            screenY[i] = -9999;
            continue;
        }

        float px = clip.x / clip.w;
        float py = clip.y / clip.w;

        screenX[i] = (int)((px + 1.0f) * 0.5f * WINDOW_WIDTH);
        screenY[i] = (int)((1.0f - py) * 0.5f * WINDOW_HEIGHT);
    }

    // draw edges — nice cyan color for objects
    SDL_SetRenderDrawColor(r, 100, 220, 255, 255);

    for(int i = 0; i < obj->edgeCount; i++) {
        int v1 = obj->edges[i][0];
        int v2 = obj->edges[i][1];

        if(screenX[v1] == -9999 || screenX[v2] == -9999)
            continue;

        SDL_RenderDrawLine(r,
            screenX[v1], screenY[v1],
            screenX[v2], screenY[v2]
        );
    }
}

// ─────────────────────────────────────────
// Draw Ground Grid
// ─────────────────────────────────────────

void drawGrid(SDL_Renderer* r, Mat4x4 proj, Mat4x4 view) {

    // grid settings
    int   gridSize  = 20;    // how many lines each side
    float gridStep  = 2.0f;  // space between lines
    float gridY     = -1.0f; // ground level

    // dim grey color for grid
    SDL_SetRenderDrawColor(r, 60, 60, 65, 255);

    Mat4x4 vp = mat4_multiply(proj, view);

    for(int i = -gridSize; i <= gridSize; i++) {

        float pos = i * gridStep;

        // line along Z axis
        Vec3 startZ = vec3(pos,       gridY, -gridSize * gridStep);
        Vec3 endZ   = vec3(pos,       gridY,  gridSize * gridStep);

        // line along X axis
        Vec3 startX = vec3(-gridSize * gridStep, gridY, pos);
        Vec3 endX   = vec3( gridSize * gridStep, gridY, pos);

        // project start and end of Z line
        Vec4 cs = mat4_multiply_vec4(vp, vec4(startZ.x, startZ.y, startZ.z, 1.0f));
        Vec4 ce = mat4_multiply_vec4(vp, vec4(endZ.x,   endZ.y,   endZ.z,   1.0f));

        if(cs.w > 0.0f && ce.w > 0.0f) {
            int x1 = (int)(( cs.x/cs.w + 1.0f) * 0.5f * WINDOW_WIDTH);
            int y1 = (int)((1.0f - cs.y/cs.w)  * 0.5f * WINDOW_HEIGHT);
            int x2 = (int)(( ce.x/ce.w + 1.0f) * 0.5f * WINDOW_WIDTH);
            int y2 = (int)((1.0f - ce.y/ce.w)  * 0.5f * WINDOW_HEIGHT);
            SDL_RenderDrawLine(r, x1, y1, x2, y2);
        }

        // project start and end of X line
        Vec4 cs2 = mat4_multiply_vec4(vp, vec4(startX.x, startX.y, startX.z, 1.0f));
        Vec4 ce2 = mat4_multiply_vec4(vp, vec4(endX.x,   endX.y,   endX.z,   1.0f));

        if(cs2.w > 0.0f && ce2.w > 0.0f) {
            int x1 = (int)(( cs2.x/cs2.w + 1.0f) * 0.5f * WINDOW_WIDTH);
            int y1 = (int)((1.0f - cs2.y/cs2.w)  * 0.5f * WINDOW_HEIGHT);
            int x2 = (int)(( ce2.x/ce2.w + 1.0f) * 0.5f * WINDOW_WIDTH);
            int y2 = (int)((1.0f - ce2.y/ce2.w)  * 0.5f * WINDOW_HEIGHT);
            SDL_RenderDrawLine(r, x1, y1, x2, y2);
        }
    }

    // draw center lines brighter — X axis and Z axis
    SDL_SetRenderDrawColor(r, 100, 100, 110, 255);

    // center Z line
    Vec4 czs = mat4_multiply_vec4(vp, vec4(0, gridY, -gridSize*gridStep, 1.0f));
    Vec4 cze = mat4_multiply_vec4(vp, vec4(0, gridY,  gridSize*gridStep, 1.0f));
    if(czs.w > 0.0f && cze.w > 0.0f) {
        int x1 = (int)((czs.x/czs.w + 1.0f) * 0.5f * WINDOW_WIDTH);
        int y1 = (int)((1.0f - czs.y/czs.w) * 0.5f * WINDOW_HEIGHT);
        int x2 = (int)((cze.x/cze.w + 1.0f) * 0.5f * WINDOW_WIDTH);
        int y2 = (int)((1.0f - cze.y/cze.w) * 0.5f * WINDOW_HEIGHT);
        SDL_RenderDrawLine(r, x1, y1, x2, y2);
    }

    // center X line
    Vec4 cxs = mat4_multiply_vec4(vp, vec4(-gridSize*gridStep, gridY, 0, 1.0f));
    Vec4 cxe = mat4_multiply_vec4(vp, vec4( gridSize*gridStep, gridY, 0, 1.0f));
    if(cxs.w > 0.0f && cxe.w > 0.0f) {
        int x1 = (int)((cxs.x/cxs.w + 1.0f) * 0.5f * WINDOW_WIDTH);
        int y1 = (int)((1.0f - cxs.y/cxs.w) * 0.5f * WINDOW_HEIGHT);
        int x2 = (int)((cxe.x/cxe.w + 1.0f) * 0.5f * WINDOW_WIDTH);
        int y2 = (int)((1.0f - cxe.y/cxe.w) * 0.5f * WINDOW_HEIGHT);
        SDL_RenderDrawLine(r, x1, y1, x2, y2);
    }
}

// ─────────────────────────────────────────
// Scene functions
// ─────────────────────────────────────────

void scene_init(Scene* s) {
    s->count = 0;
}

void scene_addCube(Scene* s, Vec3 position, float size) {
    if(s->count >= MAX_OBJECTS) {
        TV_WARN("scene full");
        return;
    }
    generateCube(&s->objects[s->count], size);
    s->objects[s->count].position = position;
    s->count++;
    TV_LOG("cube added");
}

void scene_removeLast(Scene* s) {
    if(s->count > 0) {
        s->count--;
        TV_LOG("cube removed");
    }
}

void scene_render(Scene* s, SDL_Renderer* r, Mat4x4 proj, Mat4x4 view) {
    for(int i = 0; i < s->count; i++) {
        Mat4x4 model = mat4_translate(s->objects[i].position);
        Mat4x4 vp    = mat4_multiply(proj, view);
        Mat4x4 mvp   = mat4_multiply(vp, model);
        drawObject(r, &s->objects[i], mvp);
    }
}

// ─────────────────────────────────────────
// Camera functions
// ─────────────────────────────────────────

void camera_init(Camera* cam) {
    cam->position    = vec3(0.0f, 2.0f, 8.0f);
    cam->yaw         = 0.0f;
    cam->pitch       = 0.0f;
    cam->speed       = 0.08f;
    cam->sensitivity = 0.002f;
}

void camera_update(Camera* cam, const Uint8* keys) {

    Vec3 forward;

    forward.x = sinf(cam->yaw) * cosf(cam->pitch);
    forward.y = sinf(cam->pitch);
    forward.z = -cosf(cam->yaw) * cosf(cam->pitch);

    forward = vec3_normalize(forward);

    Vec3 right;
    right.x =  cosf(cam->yaw);
    right.y =  0.0f;
    right.z =  sinf(cam->yaw);

    if(keys[SDL_SCANCODE_W])
        cam->position = vec3_add(cam->position, vec3_scale(forward, cam->speed));

    if(keys[SDL_SCANCODE_S])
        cam->position = vec3_sub(cam->position, vec3_scale(forward, cam->speed));

    if(keys[SDL_SCANCODE_A])
        cam->position = vec3_sub(cam->position, vec3_scale(right, cam->speed));

    if(keys[SDL_SCANCODE_D])
        cam->position = vec3_add(cam->position, vec3_scale(right, cam->speed));

    if(keys[SDL_SCANCODE_SPACE])
        cam->position.y += cam->speed;

    if(keys[SDL_SCANCODE_LSHIFT])
        cam->position.y -= cam->speed;
}

Vec3 camera_getTarget(Camera* cam) {
    Vec3 target;
    target.x = cam->position.x + sinf(cam->yaw)   * cosf(cam->pitch);
    target.y = cam->position.y + sinf(cam->pitch);
    target.z = cam->position.z - cosf(cam->yaw)   * cosf(cam->pitch);
    return target;
}

// ─────────────────────────────────────────
// Save world to .tvw file
// ─────────────────────────────────────────

void scene_save(Scene * s,const char * filename){

    FILE * f = fopen(filename,"w");

    if(!f){
        TV_ERROR("Failed to save world");
        return ;
    }

    // write object count first
    fprintf(f,"%d\n",s->count);

    // write each object 

    for(int i = 0;i < s->count;i += 1){
        
        /// we need to store position and size
        // size = distance between two opposite vertices
        // vertex[6] - vertex[0] gives us the full diagonal
        // but simpler - store the x extent as size

        float size = s->objects[i].vertices[1].x - s->objects[i].vertices[0].x;

        fprintf(f,"%.4f %.4f %.4f %.4f\n",
            s->objects[i].position.x,
            s->objects[i].position.y,
            s->objects[i].position.z,
            size
        );
    }
    fclose(f);
    TV_LOG("World Saved !!");
    printf("World saved to %s\n",filename);
}

// ─────────────────────────────────────────
// Load world from .tvw file
// ─────────────────────────────────────────

void scene_load(Scene * s,const char * filename){

    FILE * f = fopen(filename,"r");

    if(!f){
        TV_ERROR("Save file not found");
        return ;
    }

    // clear current scene
    s->count = 0;

    int count = 0;
    fscanf(f,"%d",&count);

    for(int i = 0;i < count;i += 1){

        float x, y, z, size;
        fscanf(f,"%f %f %f %f",&x,&y,&z,&size);

        Vec3 pos = vec3(x,y,z);
        scene_addCube(s,pos,size);
    }

    fclose(f);
    TV_LOG("World Loaded");
    printf("World loaded from %s - %d objects\n",filename,count);
}

// ─────────────────────────────────────────
// Main
// ─────────────────────────────────────────

int main(int argc, char* argv[]) {

    float currCubeSize = CURRENT_CUBE_SIZE;
    char worldfile[128] = "world.tvw";

    printf("Teravox Engine v1\n");
    printf("-----------------\n");
    printf("Enter initial cube size (0.01 to 10.0): ");
    fflush(stdout);
    scanf("%f",&currCubeSize);
    fflush(stdin);

    printf("Load existing world? (y/n) : ");
    char choice;
    scanf("%c",&choice);
    fflush(stdin);

    if(choice == 'y' || choice == 'Y'){
        printf("Enter filename (default : world.tvw):");
        scanf("%s",worldfile);
    }

    // clamp cube size
    if(currCubeSize < MIN_CUBE_SIZE)currCubeSize = MIN_CUBE_SIZE;
    if(currCubeSize >  MAX_CUBE_SIZE)currCubeSize = MAX_CUBE_SIZE;

    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        TV_ERROR("SDL init failed");
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "Teravox Engine v1",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if(!window) {
        TV_ERROR("Window creation failed");
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(
        window, -1,
        SDL_RENDERER_ACCELERATED
    );

    if(!renderer) {
        TV_ERROR("Renderer creation failed");
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    TV_LOG("Teravox started");

    // init scene
    Scene scene;
    scene_init(&scene);
    
    if(choice == 'y' || choice == 'Y'){
        scene_load(&scene,worldfile);
    }else{
        scene_addCube(&scene,vec3(0, 0, 0),currCubeSize);
    }

    // init camera
    Camera cam;
    camera_init(&cam);

    SDL_SetRelativeMouseMode(SDL_TRUE);

    int running = 1;
    SDL_Event event;

    while(running) {

        while(SDL_PollEvent(&event)) {

            if(event.type == SDL_QUIT)
                running = 0;

            if(event.type == SDL_KEYDOWN) {

                if(event.key.keysym.sym == SDLK_ESCAPE)
                    running = 0;

                // press 1 — place cube at camera position
                if(event.key.keysym.sym == SDLK_1) {

                    Vec3 forward;

                    forward.x = sinf(cam.yaw) * cosf(cam.pitch);
                    forward.y = sinf(cam.pitch);
                    forward.z = -cosf(cam.yaw) * cosf(cam.pitch);

                    // normalize direction
                    forward = vec3_normalize(forward);

                    // spawn distance from camera
                    float spawnDistance = 1.5f;

                    // final cube position
                    Vec3 placePos = vec3_add(
                        cam.position,
                        vec3_scale(forward, spawnDistance)
                    );

                    scene_addCube(&scene, placePos, currCubeSize);
                }

                // press 2 — remove last cube
                if(event.key.keysym.sym == SDLK_2) {
                    scene_removeLast(&scene);
                }

                //press up arrow to increase cube size
                if(event.key.keysym.sym == SDLK_UP){
                    if(currCubeSize < MAX_CUBE_SIZE){
                        currCubeSize += 0.05f;
                    }
                }

                //press down arrow to decrease cube size
                if(event.key.keysym.sym == SDLK_DOWN){
                    if(currCubeSize > MIN_CUBE_SIZE){
                        currCubeSize -= 0.05f;
                    }
                }

                //Ctrl + S - save world
                if(event.key.keysym.sym == SDLK_s){
                    const Uint8* modkeys = SDL_GetKeyboardState(NULL);
                    if(modkeys[SDL_SCANCODE_LCTRL] || (modkeys[SDL_SCANCODE_RCTRL])){
                        scene_save(&scene,"world.tvw");
                    }
                }

                // Ctrl + L - load world
                if(event.key.keysym.sym == SDLK_l){
                    const Uint8* modkeys = SDL_GetKeyboardState(NULL);
                    if(modkeys[SDL_SCANCODE_LCTRL] || modkeys[SDL_SCANCODE_RCTRL]){
                        scene_load(&scene,"world.tvw");
                    }
                }
            }

            if(event.type == SDL_MOUSEMOTION) {
                cam.yaw   += event.motion.xrel * cam.sensitivity;
                cam.pitch -= event.motion.yrel * cam.sensitivity;
                if(cam.pitch >  1.5f) cam.pitch =  1.5f;
                if(cam.pitch < -1.5f) cam.pitch = -1.5f;
            }
        }

        const Uint8* keys = SDL_GetKeyboardState(NULL);
        camera_update(&cam, keys);

        Vec3   target = camera_getTarget(&cam);
        Mat4x4 view   = mat4_lookat(cam.position, target, vec3(0,1,0));
        Mat4x4 proj   = mat4_perspective(
            60.0f,
            (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT,
            0.1f,
            1000.0f
        );

        // background — dark warm grey feels real
        SDL_SetRenderDrawColor(renderer, 30, 30, 35, 255);
        SDL_RenderClear(renderer);

        // draw grid first — behind everything
        drawGrid(renderer, proj, view);

        // draw all objects on top
        scene_render(&scene, renderer, proj, view);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    TV_LOG("Teravox shutting down");
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}