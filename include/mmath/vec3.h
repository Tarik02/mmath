#ifndef MMATH_VEC3_H
#define MMATH_VEC3_H

#include "mmath.h"

#pragma pack(push,1)
typedef union vec3 {
  float data[3];
  struct { float x, y, z; };
  struct { float r, g, b; };
  struct { float s, t, p; };
} vec3;
#pragma pack(pop)

MMATH_EXPORT vec3 *vec3_create();
MMATH_EXPORT void vec3_free(vec3 *a);
MMATH_EXPORT vec3 *vec3_clone(const vec3 *a);
MMATH_EXPORT vec3 *vec3_from_values(float x, float y, float z);
MMATH_EXPORT vec3 *vec3_copy(vec3 *out, const vec3 *a);
MMATH_EXPORT vec3 *vec3_zero(vec3 *out);
MMATH_EXPORT vec3 *vec3_set(vec3 *out, float x, float y, float z);

MMATH_EXPORT vec3 *vec3_add(vec3 *out, const vec3 *a, const vec3 *b);
MMATH_EXPORT vec3 *vec3_subtract(vec3 *out, const vec3 *a, const vec3 *b);
MMATH_EXPORT vec3 *vec3_multiply(vec3 *out, const vec3 *a, const vec3 *b);
MMATH_EXPORT vec3 *vec3_divide(vec3 *out, const vec3 *a, const vec3 *b);

MMATH_EXPORT vec3 *vec3_ceil(vec3 *out, const vec3 *a);
MMATH_EXPORT vec3 *vec3_floor(vec3 *out, const vec3 *a);
MMATH_EXPORT vec3 *vec3_round(vec3 *out, const vec3 *a);

MMATH_EXPORT vec3 *vec3_min(vec3 *out, const vec3 *a, const vec3 *b);
MMATH_EXPORT vec3 *vec3_max(vec3 *out, const vec3 *a, const vec3 *b);

MMATH_EXPORT vec3 *vec3_scale(vec3 *out, const vec3 *a, float b);
MMATH_EXPORT vec3 *vec3_scale_and_add(vec3 *out, const vec3 *a, const vec3 *b, float scale);

MMATH_EXPORT float vec3_distance(const vec3 *a, const vec3 *b);
MMATH_EXPORT float vec3_distance_squared(const vec3 *a, const vec3 *b);
MMATH_EXPORT float vec3_length(const vec3 *a);
MMATH_EXPORT float vec3_length_squared(const vec3 *a);

MMATH_EXPORT vec3 *vec3_negate(vec3 *out, const vec3 *a);
MMATH_EXPORT vec3 *vec3_inverse(vec3 *out, const vec3 *a);
MMATH_EXPORT vec3 *vec3_normalize(vec3 *out, const vec3 *a);

MMATH_EXPORT float vec3_dot(const vec3 *a, const vec3 *b);
MMATH_EXPORT vec3 *vec3_cross(vec3 *out, const vec3 *a, const vec3 *b);
MMATH_EXPORT vec3 *vec3_lerp(vec3 *out, const vec3 *a, const vec3 *b, float t);

MMATH_EXPORT vec3 *vec3_hermite(vec3 *out, const vec3 *a, const vec3 *b, const vec3 *c, const vec3 *d, float t);
MMATH_EXPORT vec3 *vec3_bezier(vec3 *out, const vec3 *a, const vec3 *b, const vec3 *c, const vec3 *d, float t);

MMATH_EXPORT vec3 *vec3_random(vec3 *out, float scale);

MMATH_EXPORT vec3 *vec3_transform_mat3(vec3 *out, const vec3 *a, mat3 *m);
MMATH_EXPORT vec3 *vec3_transform_mat4(vec3 *out, const vec3 *a, mat4 *m);
// TODO: Quat?

MMATH_EXPORT vec3 *vec3_rotate_x(vec3 *out, const vec3 *a, const vec3 *b, float c);
MMATH_EXPORT vec3 *vec3_rotate_y(vec3 *out, const vec3 *a, const vec3 *b, float c);
MMATH_EXPORT vec3 *vec3_rotate_z(vec3 *out, const vec3 *a, const vec3 *b, float c);
MMATH_EXPORT float vec3_angle(const vec3 *a, const vec3 *b);

MMATH_EXPORT bool vec3_exact_equals(const vec3 *a, const vec3 *b);
MMATH_EXPORT bool vec3_equals(const vec3 *a, const vec3 *b);

#endif // MMATH_VEC3_H
