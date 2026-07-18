#ifndef INC_VEC3_H
#define INC_VEC3_H

typedef struct {
    float x;
    float y;
    float z;
} vec3;

inline float* _vec3_value_ptr(vec3* vec) {
    return &vec->x;
}

#define vec3(x, y, z) (vec3){ x, y, z }

vec3 vec3_normalize(vec3 v);

vec3 vec3_add(vec3 u, vec3 v);
vec3 vec3_sub(vec3 u, vec3 v);
vec3 vec3_cross(vec3 u, vec3 v);
float vec3_dot(vec3 u, vec3 v);

#endif
