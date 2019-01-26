#ifndef MMATH_H
#define MMATH_H

#include <stdbool.h>
#include <stddef.h>

#if defined(_MSC_VER)
    //  Microsoft
    #define MMATH_EXPORT __declspec(dllexport)
    #define MMATH_IMPORT __declspec(dllimport)
#elif defined(__GNUC__)
    //  GCC
    #define MMATH_EXPORT __attribute__((visibility("default")))
    #define MMATH_IMPORT
#else
    //  do nothing and hope for the best?
    #define MMATH_EXPORT
    #define MMATH_IMPORT
    #pragma warning Unknown dynamic link import/export semantics.
#endif

typedef union mat2 mat2;
typedef union mat2d mat2d;
typedef union mat3 mat3;
typedef union mat4 mat4;

typedef union quat quat;
typedef union quat2 quat2;

typedef union vec2 vec2;
typedef union vec3 vec3;
typedef union vec4 vec4;

#define MMATH_EPSILON 0.000001f

#include "mmath/common.h"

#include "mmath/mat2.h"
#include "mmath/mat2d.h"
#include "mmath/mat3.h"
#include "mmath/mat4.h"

#include "mmath/quat.h"
#include "mmath/quat2.h"

#include "mmath/vec2.h"
#include "mmath/vec3.h"
#include "mmath/vec4.h"

#endif // MMATH_H
