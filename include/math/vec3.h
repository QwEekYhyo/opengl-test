#ifndef INC_VEC3_H
#define INC_VEC3_H

typedef struct {
    float x;
    float y;
    float z;
} vec3_t;

inline float* _vec3_value_ptr(vec3_t* vec) {
    return &vec->x;
}

#define vec3(x, y, z) { x, y, z }

#endif
