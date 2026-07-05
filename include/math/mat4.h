#ifndef INC_MAT4_H
#define INC_MAT4_H

#include <math/vec3.h>

// Uses column-major order to fit OpenGL
typedef struct {
    float buf[16];
} mat4;

inline float* _mat4_value_ptr(mat4* mat) {
    return mat->buf;
}

#define MAT4_IDENTITY (mat4){ .buf = { \
    1.0f, 0.0f, 0.0f, 0.0f,            \
    0.0f, 1.0f, 0.0f, 0.0f,            \
    0.0f, 0.0f, 1.0f, 0.0f,            \
    0.0f, 0.0f, 0.0f, 1.0f             \
} }

mat4 mat4_translate(vec3 t);

mat4 mat4_scale(vec3 s);

mat4 mat4_rotate_x(float angle);
mat4 mat4_rotate_y(float angle);
mat4 mat4_rotate_z(float angle);

mat4 mat4_mul(mat4 a, mat4 b);

#endif
