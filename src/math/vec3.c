#include <math/vec3.h>

#include <math.h>

vec3 vec3_normalize(vec3 v) {
    float norm = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);

    return (vec3){
        v.x / norm,
        v.y / norm,
        v.z / norm,
    };
}

vec3 vec3_add(vec3 u, vec3 v) {
    return (vec3){
        u.x + v.x,
        u.y + v.y,
        u.z + v.z,
    };
}

vec3 vec3_sub(vec3 u, vec3 v) {
    return (vec3){
        u.x - v.x,
        u.y - v.y,
        u.z - v.z,
    };
}

vec3 vec3_cross(vec3 u, vec3 v) {
    return (vec3){
        u.y * v.z - u.z * v.y,
        u.z * v.x - u.x * v.z,
        u.x * v.y - u.y * v.x,
    };
}

float vec3_dot(vec3 u, vec3 v) {
    return u.x * v.x + u.y * v.y + u.z * v.z;
}
