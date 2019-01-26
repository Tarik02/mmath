#ifndef MMATH_MAT4_H
#define MMATH_MAT4_H

#include "mmath.h"

#pragma pack(push,1)
typedef union mat4 {
  float data[16];
  struct {
    float m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23, m30, m31, m32, m33;
  };
} mat4;
#pragma pack(pop)

MMATH_EXPORT mat4 *mat4_create();
MMATH_EXPORT void mat4_free(mat4 *a);
MMATH_EXPORT mat4 *mat4_clone(const mat4 *a);
MMATH_EXPORT mat4 *mat4_from_values(
  float m00,
  float m01,
  float m02,
  float m03,
  float m10,
  float m11,
  float m12,
  float m13,
  float m20,
  float m21,
  float m22,
  float m23,
  float m30,
  float m31,
  float m32,
  float m33
);

MMATH_EXPORT mat4 *mat4_copy(mat4 *out, const mat4 *a);
MMATH_EXPORT mat4 *mat4_identity(mat4 *out);
MMATH_EXPORT mat4 *mat4_set(
  mat4 *out,
  float m00,
  float m01,
  float m02,
  float m03,
  float m10,
  float m11,
  float m12,
  float m13,
  float m20,
  float m21,
  float m22,
  float m23,
  float m30,
  float m31,
  float m32,
  float m33
);

MMATH_EXPORT mat4 *mat4_transpose(mat4 *out, const mat4 *a);
MMATH_EXPORT mat4 *mat4_invert(mat4 *out, const mat4 *a);
MMATH_EXPORT mat4 *mat4_adjoint(mat4 *out, const mat4 *a);
MMATH_EXPORT float mat4_determinant(const mat4 *a);
MMATH_EXPORT mat4 *mat4_multiply(mat4 *out, const mat4 *a, const mat4 *b);

MMATH_EXPORT mat4 *mat4_translate(mat4 *out, const mat4 *a, const vec4 *v);
MMATH_EXPORT mat4 *mat4_rotate(mat4 *out, const mat4 *a, float angle, const vec3 *axis);
MMATH_EXPORT mat4 *mat4_rotate_x(mat4 *out, const mat4 *a, float angle);
MMATH_EXPORT mat4 *mat4_rotate_y(mat4 *out, const mat4 *a, float angle);
MMATH_EXPORT mat4 *mat4_rotate_z(mat4 *out, const mat4 *a, float angle);
MMATH_EXPORT mat4 *mat4_scale(mat4 *out, const mat4 *a, const vec4 *v);

MMATH_EXPORT mat4 *mat4_from_translation(mat4 *out, const vec4 *v);
MMATH_EXPORT mat4 *mat4_from_rotation(mat4 *out, float angle, const vec3 *axis);
MMATH_EXPORT mat4 *mat4_from_rotation_x(mat4 *out, float angle);
MMATH_EXPORT mat4 *mat4_from_rotation_y(mat4 *out, float angle);
MMATH_EXPORT mat4 *mat4_from_rotation_z(mat4 *out, float angle);
MMATH_EXPORT mat4 *mat4_from_scaling(mat4 *out, const vec4 *v);
MMATH_EXPORT mat4 *mat4_from_rotation_translation(mat4 *out, const quat *q, const vec3 *v);
MMATH_EXPORT mat4 *mat4_from_quat2(mat4 *out, const quat2 *a);

MMATH_EXPORT vec3 *mat4_get_translation(vec3 *out, const mat4 *m);
MMATH_EXPORT quat *mat4_get_rotation(quat *out, const mat4 *m);
MMATH_EXPORT vec3 *mat4_get_scaling(vec3 *out, const mat4 *m);

MMATH_EXPORT mat4 *mat4_from_rotation_translation_scale(
  mat4 *out,
  const quat *q,
  const vec3 *v,
  const vec3 *s
);
MMATH_EXPORT mat4 *mat4_from_rotation_translation_scale_origin(
  mat4 *out,
  const quat *q,
  const vec3 *v,
  const vec3 *s,
  const vec3 *o
);
MMATH_EXPORT mat4 *mat4_from_quat(
  mat4 *out,
  const quat *q
);

MMATH_EXPORT mat4 *mat4_frustum(
  mat4 *out,
  float left,
  float right,
  float bottom,
  float top,
  float near,
  float far
);
MMATH_EXPORT mat4 *mat4_perspective(
  mat4 *out,
  float fovy,
  float aspect,
  float near,
  float far
);

MMATH_EXPORT mat4 *mat4_perspective_from_field_of_view(
  mat4 *out,
  float fovUp,
  float fovDown,
  float fovLeft,
  float fovRight,
  float near,
  float far
);

MMATH_EXPORT mat4 *mat4_ortho(
  mat4 *out,
  float left,
  float right,
  float bottom,
  float top,
  float near,
  float far
);

MMATH_EXPORT mat4 *mat4_look_at(
  mat4 *out,
  const vec3 *eye,
  const vec3 *center,
  const vec3 *up
);

MMATH_EXPORT mat4 *mat4_target_to(
  mat4 *out,
  const vec3 *eye,
  const vec3 *target,
  const vec3 *up
);

MMATH_EXPORT float mat4_frob(const mat4 *a);

MMATH_EXPORT mat4 *mat4_add(mat4 *out, const mat4 *a, const mat4 *b);
MMATH_EXPORT mat4 *mat4_subtract(mat4 *out, const mat4 *a, const mat4 *b);

MMATH_EXPORT mat4 *mat4_multiply_scalar(mat4 *out, const mat4 *a, float scale);
MMATH_EXPORT mat4 *mat4_multiply_scalar_and_add(mat4 *out, const mat4 *a, const mat4 *b, float scale);

MMATH_EXPORT bool mat4_exact_equals(const mat4 *a, const mat4 *b);
MMATH_EXPORT bool mat4_equals(const mat4 *a, const mat4 *b);

#endif // MMATH_MAT4_H
