#ifndef TERAVOX_TV_MATH_H
#define TERAVOX_TV_MATH_H

#include <math.h>

//defining macros //
#define TV_PI       3.14159265f
#define TV_DEG2RAD  0.0174532925f
#define TV_RAD2DEG  57.2957795f
#define TV_EPSILON  1e-6f

// ─────────────────────────────────────────
// Vec2 — 2D Vector
// ─────────────────────────────────────────

typedef struct{
    float x;
    float y;
}Vec2;

//Vec2 functions

static inline Vec2 vec2(float x,float y){
    Vec2 v;
    v.x = x;
    v.y = y;
    return v;
}

static inline Vec2 vec2_add(Vec2 a,Vec2 b){
    Vec2 v;
    v.x = a.x + b.x;
    v.y = a.y + b.y;
    return v;
}

static inline Vec2 vec2_sub(Vec2 a,Vec2 b){
    Vec2 v;
    v.x = a.x - b.x;
    v.y = a.y - b.y;
    return v;
}

static inline Vec2 vec2_scale(Vec2 a,float s){
    Vec2 v;
    v.x = a.x * s;
    v.y = a.y * s;
    return v;
}

static inline float vec2_dot(Vec2 a,Vec2 b){
    return (a.x * b.x + a.y * b.y);
}

static inline float vec2_magnitude(Vec2 a){
    return sqrtf((a.x * a.x) + (a.y * a.y));
}

static inline Vec2 vec2_normalize(Vec2 a){
    float mag = vec2_magnitude(a);
    if(fabs(mag) < TV_EPSILON)return a;
    return vec2_scale(a,1.0f/mag);
}

// ─────────────────────────────────────────
// Vec3 — 3D Vector
// ─────────────────────────────────────────

typedef struct{
    float x;
    float y;
    float z;
}Vec3;

//Vec3 functions 

static inline Vec3 vec3(float x,float y,float z){
    Vec3 v;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

static inline Vec3 vec3_add(Vec3 a,Vec3 b){
    Vec3 v;
    v.x = a.x + b.x;
    v.y = a.y + b.y;
    v.z = a.z + b.z;
    return v;
}

static inline Vec3 vec3_sub(Vec3 a,Vec3 b){
    Vec3 v;
    v.x = a.x - b.x;
    v.y = a.y - b.y;
    v.z = a.z - b.z;
    return v;
}

static inline Vec3 vec3_scale(Vec3 a,float s){
    Vec3 v;
    v.x = a.x * s;
    v.y = a.y * s;
    v.z = a.z * s;
    return v;
}

static inline float vec3_dot(Vec3 a,Vec3 b){
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

static inline float vec3_magnitude(Vec3 a){
    return sqrtf((a.x * a.x) + (a.y * a.y) + (a.z * a.z));
}

static inline Vec3 vec3_normalize(Vec3 a){
    float mag = vec3_magnitude(a);
    if(fabs(mag) < TV_EPSILON)return a;
    return vec3_scale(a,1.0f/mag);
}

static inline Vec3 vec3_cross(Vec3 a,Vec3 b){
    Vec3 v;
    v.x = a.y * b.z - a.z * b.y;
    v.y = a.z * b.x - a.x * b.z;
    v.z = a.x * b.y - a.y * b.x;
    return v;
}

static inline Vec3 vec3_negate(Vec3 a){
    Vec3 v;
    v.x = -a.x;
    v.y = -a.y;
    v.z = -a.z;
    return v;
}

static inline Vec3 vec3_lerp(Vec3 a,Vec3 b,float t){
    Vec3 v;
    v = vec3_add(a,vec3_scale(vec3_sub(b,a),t));
    return v;
}

// ─────────────────────────────────────────
// Vec4 — 4D Vector
// ─────────────────────────────────────────

typedef struct{
    float x;
    float y;
    float z;
    float w;
}Vec4;

//Vec4 functions 

static inline Vec4 vec4(float x,float y,float z,float w){
    Vec4 v;
    v.x = x;
    v.y = y;
    v.z = z;
    v.w = w;
    return v;
}

static inline Vec4 vec4_add(Vec4 a,Vec4 b){
    Vec4 v;
    v.x = a.x + b.x;
    v.y = a.y + b.y;
    v.z = a.z + b.z;
    v.w = a.w + b.w;
    return v;
}

static inline Vec4 vec4_sub(Vec4 a,Vec4 b){
    Vec4 v;
    v.x = a.x - b.x;
    v.y = a.y - b.y;
    v.z = a.z - b.z;
    v.w = a.w - b.w;
    return v;
}

static inline Vec4 vec4_scale(Vec4 a,float s){
    Vec4 v;
    v.x = a.x * s;
    v.y = a.y * s;
    v.z = a.z * s;
    v.w = a.w * s;
    return v;
}

static inline float vec4_dot(Vec4 a,Vec4 b){
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

// ─────────────────────────────────────────
// Matrix 4x4 structure
// ─────────────────────────────────────────

typedef struct{
    float m[4][4];
}Mat4x4;

// matrix functions 

static inline Mat4x4 mat4_identity(){
    Mat4x4 mat;
    for(int i = 0;i < 4;i += 1){
        for(int j = 0;j < 4;j += 1){
            if(i == j){
                mat.m[i][j] = 1.0f;
            }else{
                mat.m[i][j] = 0.0f;
            }
        }
    }
    return mat;
}

static inline Mat4x4 mat4_zero(){
    Mat4x4 mat;
    for(int i = 0;i < 4;i += 1){
        for(int j = 0;j < 4;j += 1){
            mat.m[i][j] = 0.0f;
        }
    }
    return mat;
}

static inline Mat4x4 mat4_multiply(Mat4x4 a,Mat4x4 b){
    Mat4x4 mat = mat4_zero();
    for(int i = 0;i < 4;i += 1){
        for(int j = 0;j < 4;j += 1){
            for(int k = 0;k < 4;k += 1){
                mat.m[i][j] += a.m[i][k] * b.m[k][j];
            }
        }
    }
    return mat;
}

static inline Vec4 mat4_multiply_vec4(Mat4x4 mat,Vec4 v){
    Vec4 vec;
    vec.x = mat.m[0][0] * v.x + mat.m[0][1] * v.y + mat.m[0][2] * v.z + mat.m[0][3] * v.w;
    vec.y = mat.m[1][0] * v.x + mat.m[1][1] * v.y + mat.m[1][2] * v.z + mat.m[1][3] * v.w;
    vec.z = mat.m[2][0] * v.x + mat.m[2][1] * v.y + mat.m[2][2] * v.z + mat.m[2][3] * v.w;
    vec.w = mat.m[3][0] * v.x + mat.m[3][1] * v.y + mat.m[3][2] * v.z + mat.m[3][3] * v.w;
    return vec;
}

// translation matrix //

static inline Mat4x4 mat4_translate(Vec3 v){
    Mat4x4 mat = mat4_identity();
    mat.m[0][3] = v.x;
    mat.m[1][3] = v.y;
    mat.m[2][3] = v.z;
    return mat;
}

// scaling matrix //

static inline Mat4x4 mat4_scale(Vec3 s){
    Mat4x4 mat = mat4_identity();
    mat.m[0][0] = s.x;
    mat.m[1][1] = s.y;
    mat.m[2][2] = s.z;
    return mat;
}

// Rotation X matrix //

static inline Mat4x4 mat4_rotation_x(float angle){
    float rad = angle * TV_DEG2RAD;
    Mat4x4 mat = mat4_identity();
    mat.m[1][1] = cosf(rad);
    mat.m[1][2] = -sinf(rad);
    mat.m[2][1] = sinf(rad);
    mat.m[2][2] = cosf(rad);
    return mat;
}

//Rotation Y matrix //
static inline Mat4x4 mat4_rotation_y(float angle){
    float rad = angle * TV_DEG2RAD;
    Mat4x4 mat = mat4_identity();
    mat.m[0][0] = cosf(rad);
    mat.m[0][2] = sinf(rad);
    mat.m[2][0] = -sinf(rad);
    mat.m[2][2] = cosf(rad);
    return mat;
}

//Rotation Z matrix //

static inline Mat4x4 mat4_rotation_z(float angle){
    float rad = angle * TV_DEG2RAD;
    Mat4x4 mat = mat4_identity();
    mat.m[0][0] = cosf(rad);
    mat.m[0][1] = -sinf(rad);
    mat.m[1][0] = sinf(rad);
    mat.m[1][1] = cosf(rad);
    return mat;
}

// Perspective projection matrix //

static inline Mat4x4 mat4_perspective(float fov, float aspect, float near, float far){
    Mat4x4 mat = mat4_zero();
    float rad = fov * TV_DEG2RAD;
    float f = 1.0f / tanf(rad / 2.0f);

    mat.m[0][0] = f / aspect;
    mat.m[1][1] = f;
    mat.m[2][2] = (far + near) / (near - far);
    mat.m[2][3] = (2.0f * far * near) / (near - far);
    mat.m[3][2] = -1.0f;

    return mat;
}

// Lookat view matrix //

static inline Mat4x4 mat4_lookat(Vec3 eye, Vec3 target, Vec3 up){

    // step 1 - forward vector
    Vec3 f = vec3_normalize(vec3_sub(target, eye));

    // step 2 - right vector
    Vec3 r = vec3_normalize(vec3_cross(f, up));

    // step 3 - true up vector
    Vec3 u = vec3_cross(r, f);

    Mat4x4 mat = mat4_identity();

    mat.m[0][0] = r.x;
    mat.m[0][1] = r.y;
    mat.m[0][2] = r.z;

    mat.m[1][0] = u.x;
    mat.m[1][1] = u.y;
    mat.m[1][2] = u.z;

    mat.m[2][0] = -f.x;
    mat.m[2][1] = -f.y;
    mat.m[2][2] = -f.z;

    mat.m[0][3] = -vec3_dot(r, eye);
    mat.m[1][3] = -vec3_dot(u, eye);
    mat.m[2][3] =  vec3_dot(f, eye);

    return mat;
}

#endif // TERAVOX_TV_MATH_H