#include <math/mat4.h>

#include <math/vec3.h>

mat4_t mat4_translate(mat4_t mat, const vec3_t trans) {
    mat.buf[12] += trans.x;
    mat.buf[13] += trans.y;
    mat.buf[14] += trans.z;

    return mat;
}

void mat4_translate_inplace(mat4_t* mat, const vec3_t* trans) {
    mat->buf[12] += trans->x;
    mat->buf[13] += trans->y;
    mat->buf[14] += trans->z;
}

mat4_t mat4_scale(mat4_t mat, float scale) {
    mat.buf[0]  *= scale;
    mat.buf[5]  *= scale;
    mat.buf[10] *= scale;

    return mat;
}

mat4_t mat4_scale_non_uniform(mat4_t mat, const vec3_t scale) {
    mat.buf[0]  *= scale.x;
    mat.buf[5]  *= scale.y;
    mat.buf[10] *= scale.z;

    return mat;
}
