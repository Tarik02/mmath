#ifndef MMATH_VEC2_H
#define MMATH_VEC2_H

#include "mmath.h"

#pragma pack(push,1)
typedef union vec2 {
  float data[2];
  struct { float x, y; };
  struct { float r, g; };
  struct { float s, t; };
} vec2;
#pragma pack(pop)

MMATH_EXPORT vec2 *vec2_create();
MMATH_EXPORT void vec2_free(vec2 *a);
MMATH_EXPORT vec2 *vec2_clone(const vec2 *a);
MMATH_EXPORT vec2 *vec2_from_values(float x, float y);
MMATH_EXPORT vec2 *vec2_copy(vec2 *out, const vec2 *a);
MMATH_EXPORT vec2 *vec2_zero(vec2 *out);
MMATH_EXPORT vec2 *vec2_set(vec2 *out, float x, float y);

MMATH_EXPORT vec2 *vec2_add(vec2 *out, const vec2 *a, const vec2 *b);
MMATH_EXPORT vec2 *vec2_subtract(vec2 *out, const vec2 *a, const vec2 *b);
MMATH_EXPORT vec2 *vec2_multiply(vec2 *out, const vec2 *a, const vec2 *b);
MMATH_EXPORT vec2 *vec2_divide(vec2 *out, const vec2 *a, const vec2 *b);

MMATH_EXPORT vec2 *vec2_ceil(vec2 *out, const vec2 *a);
MMATH_EXPORT vec2 *vec2_floor(vec2 *out, const vec2 *a);
MMATH_EXPORT vec2 *vec2_round(vec2 *out, const vec2 *a);

MMATH_EXPORT vec2 *vec2_min(vec2 *out, const vec2 *a, const vec2 *b);
MMATH_EXPORT vec2 *vec2_max(vec2 *out, const vec2 *a, const vec2 *b);

MMATH_EXPORT vec2 *vec2_scale(vec2 *out, const vec2 *a, float b);
MMATH_EXPORT vec2 *vec2_scale_and_add(vec2 *out, const vec2 *a, const vec2 *b, float scale);

MMATH_EXPORT float vec2_distance(const vec2 *a, const vec2 *b);
MMATH_EXPORT float vec2_distance_squared(const vec2 *a, const vec2 *b);
MMATH_EXPORT float vec2_length(const vec2 *a);
MMATH_EXPORT float vec2_length_squared(const vec2 *a);

MMATH_EXPORT vec2 *vec2_negate(vec2 *out, const vec2 *a);
MMATH_EXPORT vec2 *vec2_inverse(vec2 *out, const vec2 *a);
MMATH_EXPORT vec2 *vec2_normalize(vec2 *out, const vec2 *a);

MMATH_EXPORT float vec2_dot(const vec2 *a, const vec2 *b);
MMATH_EXPORT vec3 *vec2_cross(vec3 *out, const vec2 *a, const vec2 *b);
MMATH_EXPORT vec2 *vec2_lerp(vec2 *out, const vec2 *a, const vec2 *b, float t);

MMATH_EXPORT vec2 *vec2_random(vec2 *out, float scale);

MMATH_EXPORT vec2 *vec2_transform_mat2(vec2 *out, const vec2 *a, const mat2 *m);
MMATH_EXPORT vec2 *vec2_transform_mat2d(vec2 *out, const vec2 *a, const mat2d *m);
MMATH_EXPORT vec2 *vec2_transform_mat3(vec2 *out, const vec2 *a, const mat3 *m);
MMATH_EXPORT vec2 *vec2_transform_mat4(vec2 *out, const vec2 *a, const mat4 *m);

MMATH_EXPORT vec2 *vec2_rotate(vec2 *out, const vec2 *a, const vec2 *b, float c);
MMATH_EXPORT float vec2_angle(const vec2 *a, const vec2 *b);

MMATH_EXPORT bool vec2_exact_equals(const vec2 *a, const vec2 *b);
MMATH_EXPORT bool vec2_equals(const vec2 *a, const vec2 *b);

#endif // MMATH_VEC2_H
