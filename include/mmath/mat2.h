#ifndef MMATH_MAT2_H
#define MMATH_MAT2_H

#include "mmath.h"

#pragma pack(push,1)
typedef union mat2 {
  float data[4];
  struct {
    float m00, m01, m10, m11;
  };
} mat2;
#pragma pack(pop)

MMATH_EXPORT mat2 *mat2_create();
MMATH_EXPORT void mat2_free(mat2 *a);
MMATH_EXPORT mat2 *mat2_clone(const mat2 *a);
MMATH_EXPORT mat2 *mat2_from_values(float m00, float m01, float m10, float m11);

MMATH_EXPORT mat2 *mat2_copy(mat2 *out, const mat2 *a);
MMATH_EXPORT mat2 *mat2_identity(mat2 *out);
MMATH_EXPORT mat2 *mat2_set(mat2 *out, float m00, float m01, float m10, float m11);

MMATH_EXPORT mat2 *mat2_transpose(mat2 *out, const mat2 *a);
MMATH_EXPORT mat2 *mat2_invert(mat2 *out, const mat2 *a);
MMATH_EXPORT mat2 *mat2_adjoint(mat2 *out, const mat2 *a);
MMATH_EXPORT float mat2_determinant(const mat2 *a);
MMATH_EXPORT mat2 *mat2_multiply(mat2 *out, const mat2 *a, const mat2 *b);

MMATH_EXPORT mat2 *mat2_rotate(mat2 *out, const mat2 *a, float angle);
MMATH_EXPORT mat2 *mat2_scale(mat2 *out, const mat2 *a, const vec2 *v);

MMATH_EXPORT mat2 *mat2_from_rotation(mat2 *out, float angle);
MMATH_EXPORT mat2 *mat2_from_scaling(mat2 *out, const vec2 *v);

MMATH_EXPORT float mat2_frob(const mat2 *a);

MMATH_EXPORT mat2 *mat2_add(mat2 *out, const mat2 *a, const mat2 *b);
MMATH_EXPORT mat2 *mat2_subtract(mat2 *out, const mat2 *a, const mat2 *b);

MMATH_EXPORT mat2 *mat2_multiply_scalar(mat2 *out, const mat2 *a, float scale);
MMATH_EXPORT mat2 *mat2_multiply_scalar_and_add(mat2 *out, const mat2 *a, const mat2 *b, float scale);

MMATH_EXPORT bool mat2_exact_equals(const mat2 *a, const mat2 *b);
MMATH_EXPORT bool mat2_equals(const mat2 *a, const mat2 *b);

#endif // MMATH_MAT2_H
