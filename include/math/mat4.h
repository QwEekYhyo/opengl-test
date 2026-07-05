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
    0.0f, 0.0f, 0.0f, scalar  \
} }

#define mat4_identity() mat4(1.0f)

mat4_t mat4_translate(mat4_t mat, const vec3_t trans);
void mat4_translate_inplace(mat4_t* mat, const vec3_t* trans);

mat4_t mat4_scale(mat4_t mat, float scale);
mat4_t mat4_scale_non_uniform(mat4_t mat, const vec3_t scale);

#endif
