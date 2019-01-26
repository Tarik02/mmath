#ifndef MMATH_MAT2D_H
#define MMATH_MAT2D_H

#include "mmath.h"

#pragma pack(push,1)
typedef union mat2d {
  float data[6];
  struct {
    float a, b, c, d, tx, ty;
  };
} mat2d;
#pragma pack(pop)

MMATH_EXPORT mat2d *mat2d_create();
MMATH_EXPORT void mat2d_free(mat2d *a);
MMATH_EXPORT mat2d *mat2d_clone(const mat2d *a);
MMATH_EXPORT mat2d *mat2d_from_values(float a, float b, float c, float d, float tx, float ty);

MMATH_EXPORT mat2d *mat2d_copy(mat2d *out, const mat2d *a);
MMATH_EXPORT mat2d *mat2d_identity(mat2d *out);
MMATH_EXPORT mat2d *mat2d_set(mat2d *out, float a, float b, float c, float d, float tx, float ty);

MMATH_EXPORT mat2d *mat2d_invert(mat2d *out, const mat2d *a);
MMATH_EXPORT float mat2d_determinant(const mat2d *a);

MMATH_EXPORT mat2d *mat2d_multiply(mat2d *out, const mat2d *a, const mat2d *b);

MMATH_EXPORT mat2d *mat2d_rotate(mat2d *out, const mat2d *a, float angle);
MMATH_EXPORT mat2d *mat2d_scale(mat2d *out, const mat2d *a, const vec2 *v);
MMATH_EXPORT mat2d *mat2d_translate(mat2d *out, const mat2d *a, const vec2 *v);

MMATH_EXPORT mat2d *mat2d_from_rotation(mat2d *out, float angle);
MMATH_EXPORT mat2d *mat2d_from_scaling(mat2d *out, const vec2 *v);
MMATH_EXPORT mat2d *mat2d_from_translation(mat2d *out, const vec2 *v);

MMATH_EXPORT float mat2d_frob(const mat2d *a);

MMATH_EXPORT mat2d *mat2d_add(mat2d *out, const mat2d *a, const mat2d *b);
MMATH_EXPORT mat2d *mat2d_subtract(mat2d *out, const mat2d *a, const mat2d *b);

MMATH_EXPORT mat2d *mat2d_multiply_scalar(mat2d *out, const mat2d *a, float scale);
MMATH_EXPORT mat2d *mat2d_multiply_scalar_and_add(mat2d *out, const mat2d *a, const mat2d *b, float scale);

MMATH_EXPORT bool mat2d_exact_equals(const mat2d *a, const mat2d *b);
MMATH_EXPORT bool mat2d_equals(const mat2d *a, const mat2d *b);

#endif // MMATH_MAT2D_H
