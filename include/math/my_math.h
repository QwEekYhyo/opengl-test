#ifndef INC_MY_MATH_H
#define INC_MY_MATH_H

#include <math/mat4.h>
#include <math/vec3.h>

#define value_ptr(o) _Generic(&(o),   \
            mat4_t*: _mat4_value_ptr, \
            vec3_t*: _vec3_value_ptr  \
        )(&(o))

#endif
