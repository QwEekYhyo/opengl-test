#ifndef INC_MAT4_H
#define INC_MAT4_H

typedef struct {
    float buf[16];
} mat4_t;

#define mat4(scalar) { .buf = { \
    scalar, 0.0f, 0.0f, 0.0f, \
    0.0f, scalar, 0.0f, 0.0f, \
    0.0f, 0.0f, scalar, 0.0f, \
    0.0f, 0.0f, 0.0f, 1.0f \
} }

#define value_ptr(mat) mat.buf

typedef struct {
    float x;
    float y;
    float z;
} vec3_t;

#define vec3(x, y, z) { x, y, z }

inline void mat4_translate(mat4_t* mat, const vec3_t* trans) {
    mat->buf[12] = trans->x;
    mat->buf[13] = trans->y;
    mat->buf[14] = trans->z;
}

#endif
