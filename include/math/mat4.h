#ifndef INC_MAT4_H
#define INC_MAT4_H

#include <math/vec3.h>

typedef struct {
    float buf[16];
} mat4_t;

inline float* _mat4_value_ptr(mat4_t* mat) {
    return mat->buf;
}

#define mat4(scalar) { .buf = { \
    scalar, 0.0f, 0.0f, 0.0f, \
    0.0f, scalar, 0.0f, 0.0f, \
    0.0f, 0.0f, scalar, 0.0f, \
    0.0f, 0.0f, 0.0f, 1.0f \
} }

inline void mat4_translate(mat4_t* mat, const vec3_t* trans) {
    mat->buf[12] = trans->x;
    mat->buf[13] = trans->y;
    mat->buf[14] = trans->z;
}

#endif
