#ifndef MMATH_MAT3_H
#define MMATH_MAT3_H

#include "mmath.h"

#pragma pack(push,1)
typedef union mat3 {
  float data[9];
  struct {
    float m00, m01, m02, m10, m11, m12, m20, m21, m22;
  };
} mat3;
#pragma pack(pop)

MMATH_EXPORT mat3 *mat3_create();
MMATH_EXPORT void mat3_free(mat3 *a);
MMATH_EXPORT mat3 *mat3_clone(const mat3 *a);
MMATH_EXPORT mat3 *mat3_from_values(
  float m00,
  float m01,
  float m02,
  float m10,
  float m11,
  float m12,
  float m20,
  float m21,
  float m22
);

MMATH_EXPORT mat3 *mat3_copy(mat3 *out, const mat3 *a);
MMATH_EXPORT mat3 *mat3_identity(mat3 *out);
MMATH_EXPORT mat3 *mat3_set(
  mat3 *out,
  float m00,
  float m01,
  float m02,
  float m10,
  float m11,
  float m12,
  float m20,
  float m21,
  float m22
);

MMATH_EXPORT mat3 *mat3_transpose(mat3 *out, const mat3 *a);
MMATH_EXPORT mat3 *mat3_invert(mat3 *out, const mat3 *a);
MMATH_EXPORT mat3 *mat3_adjoint(mat3 *out, const mat3 *a);
MMATH_EXPORT float mat3_determinant(const mat3 *a);
MMATH_EXPORT mat3 *mat3_multiply(mat3 *out, const mat3 *a, const mat3 *b);

MMATH_EXPORT mat3 *mat3_translate(mat3 *out, const mat3 *a, const vec2 *v);
MMATH_EXPORT mat3 *mat3_rotate(mat3 *out, const mat3 *a, float angle);
MMATH_EXPORT mat3 *mat3_scale(mat3 *out, const mat3 *a, const vec2 *v);

MMATH_EXPORT mat3 *mat3_from_translation(mat3 *out, const vec2 *v);
MMATH_EXPORT mat3 *mat3_from_rotation(mat3 *out, float angle);
MMATH_EXPORT mat3 *mat3_from_scaling(mat3 *out, const vec2 *v);

MMATH_EXPORT mat3 *mat3_from_mat2d(mat3 *out, const mat2d *a);
MMATH_EXPORT mat3 *mat3_from_mat4(mat3 *out, const mat4 *a);
// TODO: Quat?
// TODO: normalFromMat4?

MMATH_EXPORT float mat3_frob(const mat3 *a);

MMATH_EXPORT mat3 *mat3_add(mat3 *out, const mat3 *a, const mat3 *b);
MMATH_EXPORT mat3 *mat3_subtract(mat3 *out, const mat3 *a, const mat3 *b);

MMATH_EXPORT mat3 *mat3_multiply_scalar(mat3 *out, const mat3 *a, float scale);
MMATH_EXPORT mat3 *mat3_multiply_scalar_and_add(mat3 *out, const mat3 *a, const mat3 *b, float scale);

MMATH_EXPORT mat3 *mat3_projection(mat3 *out, float width, float height);

MMATH_EXPORT bool mat3_exact_equals(const mat3 *a, const mat3 *b);
MMATH_EXPORT bool mat3_equals(const mat3 *a, const mat3 *b);

#endif // MMATH_MAT3_H
