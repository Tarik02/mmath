#ifndef MMATH_VEC4_H
#define MMATH_VEC4_H

#include "mmath.h"

#pragma pack(push,1)
typedef union vec4 {
  float data[4];
  struct { float x, y, z, w; };
  struct { float r, g, b, a; };
  struct { float s, t, p, q; };
} vec4;
#pragma pack(pop)

MMATH_EXPORT vec4 *vec4_create();
MMATH_EXPORT void vec4_free(vec4 *a);
MMATH_EXPORT vec4 *vec4_clone(const vec4 *a);
MMATH_EXPORT vec4 *vec4_from_values(float x, float y, float z, float w);
MMATH_EXPORT vec4 *vec4_copy(vec4 *out, const vec4 *a);
MMATH_EXPORT vec4 *vec4_zero(vec4 *out);
MMATH_EXPORT vec4 *vec4_set(vec4 *out, float x, float y, float z, float w);

MMATH_EXPORT vec4 *vec4_add(vec4 *out, const vec4 *a, const vec4 *b);
MMATH_EXPORT vec4 *vec4_subtract(vec4 *out, const vec4 *a, const vec4 *b);
MMATH_EXPORT vec4 *vec4_multiply(vec4 *out, const vec4 *a, const vec4 *b);
MMATH_EXPORT vec4 *vec4_divide(vec4 *out, const vec4 *a, const vec4 *b);

MMATH_EXPORT vec4 *vec4_ceil(vec4 *out, const vec4 *a);
MMATH_EXPORT vec4 *vec4_floor(vec4 *out, const vec4 *a);
MMATH_EXPORT vec4 *vec4_round(vec4 *out, const vec4 *a);

MMATH_EXPORT vec4 *vec4_min(vec4 *out, const vec4 *a, const vec4 *b);
MMATH_EXPORT vec4 *vec4_max(vec4 *out, const vec4 *a, const vec4 *b);

MMATH_EXPORT vec4 *vec4_scale(vec4 *out, const vec4 *a, float b);
MMATH_EXPORT vec4 *vec4_scale_and_add(vec4 *out, const vec4 *a, const vec4 *b, float scale);

MMATH_EXPORT float vec4_distance(const vec4 *a, const vec4 *b);
MMATH_EXPORT float vec4_distance_squared(const vec4 *a, const vec4 *b);
MMATH_EXPORT float vec4_length(const vec4 *a);
MMATH_EXPORT float vec4_length_squared(const vec4 *a);

MMATH_EXPORT vec4 *vec4_negate(vec4 *out, const vec4 *a);
MMATH_EXPORT vec4 *vec4_inverse(vec4 *out, const vec4 *a);
MMATH_EXPORT vec4 *vec4_normalize(vec4 *out, const vec4 *a);

MMATH_EXPORT float vec4_dot(const vec4 *a, const vec4 *b);
MMATH_EXPORT vec4 *vec4_cross(vec4 *out, const vec4 *u, const vec4 *v, const vec4 *w);
MMATH_EXPORT vec4 *vec4_lerp(vec4 *out, const vec4 *a, const vec4 *b, float t);

MMATH_EXPORT vec4 *vec4_random(vec4 *out, float scale);

MMATH_EXPORT vec4 *vec4_transform_mat4(vec4 *out, const vec4 *a, mat4 *m);
// TODO: Quat?

MMATH_EXPORT bool vec4_exact_equals(const vec4 *a, const vec4 *b);
MMATH_EXPORT bool vec4_equals(const vec4 *a, const vec4 *b);

#endif // MMATH_VEC4_H
