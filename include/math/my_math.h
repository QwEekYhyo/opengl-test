#ifndef INC_MY_MATH_H
#define INC_MY_MATH_H

#include <math/mat4.h>
#include <math/vec3.h>

#define value_ptr(o) _Generic(&(o), \
            mat4*: _mat4_value_ptr, \
            vec3*: _vec3_value_ptr  \
        )(&(o))

#define MY_PI 3.14159265358979323846

#define RADIANS(angle) (angles * MY_PI / 180.0f)

#endif
