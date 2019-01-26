#ifndef MMATH_QUAT_H
#define MMATH_QUAT_H

#include "mmath.h"

#pragma pack(push,1)
typedef union quat {
  float data[4];
  struct { float x, y, z, w; };
} quat;
#pragma pack(pop)

MMATH_EXPORT quat *quat_create();
MMATH_EXPORT void quat_free(quat *a);
MMATH_EXPORT quat *quat_clone(const quat *a);
MMATH_EXPORT quat *quat_from_values(float x, float y, float z, float w);
MMATH_EXPORT quat *quat_copy(quat *out, const quat *a);
MMATH_EXPORT quat *quat_identity(quat *out);
MMATH_EXPORT quat *quat_set(quat *out, float x, float y, float z, float w);

MMATH_EXPORT float quat_get_axis_angle(quat *out_axis, const quat *q);
MMATH_EXPORT quat *quat_set_axis_angle(quat *out, const vec3 *axis, float angle);

MMATH_EXPORT quat *quat_multiply(quat *out, const quat *a, const quat *b);
MMATH_EXPORT quat *quat_rotate_x(quat *out, const quat *a, float angle);
MMATH_EXPORT quat *quat_rotate_y(quat *out, const quat *a, float angle);
MMATH_EXPORT quat *quat_rotate_z(quat *out, const quat *a, float angle);
MMATH_EXPORT quat *quat_calculate_w(quat *out, const quat *a);

MMATH_EXPORT quat *quat_add(quat *out, const quat *a, const quat *b);
MMATH_EXPORT quat *quat_scale(quat *out, const quat *a, float b);

MMATH_EXPORT float quat_dot(const quat *a, const quat *b);
MMATH_EXPORT quat *quat_lerp(quat *out, const quat *a, const quat *b, float t);
MMATH_EXPORT quat *quat_slerp(quat *out, const quat *a, const quat *b, float t);

MMATH_EXPORT float quat_length(const quat *a);
MMATH_EXPORT float quat_length_squared(const quat *a);

MMATH_EXPORT quat *quat_random(quat *out);

MMATH_EXPORT quat *quat_normalize(quat *out, const quat *a);
MMATH_EXPORT quat *quat_invert(quat *out, const quat *a);
MMATH_EXPORT quat *quat_conjugate(quat *out, const quat *a);

MMATH_EXPORT quat *quat_from_mat3(quat *out, const mat3 *m);
MMATH_EXPORT quat *quat_from_euler(quat *out, float x, float y, float z);

MMATH_EXPORT bool quat_exact_equals(const quat *a, const quat *b);
MMATH_EXPORT bool quat_equals(const quat *a, const quat *b);

#endif // MMATH_QUAT_H
