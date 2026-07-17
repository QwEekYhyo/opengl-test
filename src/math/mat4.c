#include <math/mat4.h>

#include <math.h>

#include <math/vec3.h>

mat4 mat4_translate(vec3 t) {
    return (mat4){ .buf = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
         t.x,  t.y,  t.z, 1.0f,
    } };
}

mat4 mat4_scale(vec3 s) {
    return (mat4){ .buf = {
        s.x, 0.0f, 0.0f, 0.0f,
        0.0f, s.y, 0.0f, 0.0f,
        0.0f, 0.0f, s.z, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
    } };
}

mat4 mat4_rotate_x(float angle) {
    return (mat4){ .buf = {
        1.0f,         0.0f,        0.0f, 0.0f,
        0.0f,  cosf(angle), sinf(angle), 0.0f,
        0.0f, -sinf(angle), cosf(angle), 0.0f,
        0.0f,         0.0f,        0.0f, 1.0f,
    } };
}

mat4 mat4_rotate_y(float angle) {
    return (mat4){ .buf = {
        cosf(angle), 0.0f, -sinf(angle), 0.0f,
               0.0f, 1.0f,         0.0f, 0.0f,
        sinf(angle), 0.0f,  cosf(angle), 0.0f,
               0.0f, 0.0f,         0.0f, 1.0f,
    } };
}

mat4 mat4_rotate_z(float angle) {
    return (mat4){ .buf = {
         cosf(angle), sinf(angle), 0.0f, 0.0f,
        -sinf(angle), cosf(angle), 0.0f, 0.0f,
                0.0f,        0.0f, 1.0f, 0.0f,
                0.0f,        0.0f, 0.0f, 1.0f,
    } };
}

mat4 mat4_perspective(float fov, float aspect, float near, float far) {
    float f = 1.0f / tanf(fov * 0.5f);

    return (mat4){ .buf = {
        f / aspect, 0.0f,                               0.0f,  0.0f,
              0.0f,    f,                               0.0f,  0.0f,
              0.0f, 0.0f,        (far + near) / (near - far), -1.0f,
              0.0f, 0.0f, (2.0f * far * near) / (near - far),  0.0f,
    } };
}

// Column vectors
mat4 mat4_mul(mat4 a, mat4 b) {
    mat4 r;

    for (int col = 0; col < 4; col++) {
        for (int row = 0; row < 4; row++) {
            r.buf[col * 4 + row] =
                a.buf[0 * 4 + row] * b.buf[col * 4 + 0] +
                a.buf[1 * 4 + row] * b.buf[col * 4 + 1] +
                a.buf[2 * 4 + row] * b.buf[col * 4 + 2] +
                a.buf[3 * 4 + row] * b.buf[col * 4 + 3];
        }
    }

    return r;
}
