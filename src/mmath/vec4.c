#include "mmath/vec4.h"
#include "mmath_private.h"

vec4 *vec4_create() {
  vec4 *out = malloc(sizeof(vec4));
  out->x = 0.f;
  out->y = 0.f;
  out->z = 0.f;
  out->w = 0.f;
  return out;
}

void vec4_free(vec4 *a) {
  free(a);
}

vec4 *vec4_clone(const vec4 *a) {
  vec4 *out = vec4_create();
  vec4_copy(out, a);
  return out;
}

vec4 *vec4_from_values(float x, float y, float z, float w) {
  vec4 *out = vec4_create();
  out->x = x;
  out->y = y;
  out->z = z;
  out->w = w;
  return out;
}

vec4 *vec4_copy(vec4 *out, const vec4 *a) {
  out->x = a->x;
  out->y = a->y;
  out->z = a->z;
  out->w = a->w;
  return out;
}

vec4 *vec4_zero(vec4 *out) {
  return vec4_set(out, 0.f, 0.f, 0.f, 0.f);
}

vec4 *vec4_set(vec4 *out, float x, float y, float z, float w) {
  out->x = x;
  out->y = y;
  out->z = z;
  out->w = w;
  return out;
}

vec4 *vec4_add(vec4 *out, const vec4 *a, const vec4 *b) {
  out->x = a->x + b->x;
  out->y = a->y + b->y;
  out->z = a->z + b->z;
  out->w = a->w + b->w;
  return out;
}

vec4 *vec4_subtract(vec4 *out, const vec4 *a, const vec4 *b) {
  out->x = a->x - b->x;
  out->y = a->y - b->y;
  out->z = a->z - b->z;
  out->w = a->w - b->w;
  return out;
}

vec4 *vec4_multiply(vec4 *out, const vec4 *a, const vec4 *b) {
  out->x = a->x * b->x;
  out->y = a->y * b->y;
  out->z = a->z * b->z;
  out->w = a->w * b->w;
  return out;
}

vec4 *vec4_divide(vec4 *out, const vec4 *a, const vec4 *b) {
  out->x = a->x / b->x;
  out->y = a->y / b->y;
  out->z = a->z / b->z;
  out->w = a->w / b->w;
  return out;
}

vec4 *vec4_ceil(vec4 *out, const vec4 *a) {
  out->x = ceilf(a->x);
  out->y = ceilf(a->y);
  out->z = ceilf(a->z);
  out->w = ceilf(a->w);
  return out;
}

vec4 *vec4_floor(vec4 *out, const vec4 *a) {
  out->x = floorf(a->x);
  out->y = floorf(a->y);
  out->z = floorf(a->z);
  out->w = floorf(a->w);
  return out;
}

vec4 *vec4_round(vec4 *out, const vec4 *a) {
  out->x = roundf(a->x);
  out->y = roundf(a->y);
  out->z = roundf(a->z);
  out->w = roundf(a->w);
  return out;
}

vec4 *vec4_min(vec4 *out, const vec4 *a, const vec4 *b) {
  out->x = fminf(a->x, b->x);
  out->y = fminf(a->y, b->y);
  out->z = fminf(a->z, b->z);
  out->w = fminf(a->w, b->w);
  return out;
}

vec4 *vec4_max(vec4 *out, const vec4 *a, const vec4 *b) {
  out->x = fmaxf(a->x, b->x);
  out->y = fmaxf(a->y, b->y);
  out->z = fmaxf(a->z, b->z);
  out->w = fmaxf(a->z, b->w);
  return out;
}

vec4 *vec4_scale(vec4 *out, const vec4 *a, float b) {
  out->x = a->x * b;
  out->y = a->y * b;
  out->z = a->z * b;
  out->w = a->w * b;
  return out;
}

vec4 *vec4_scale_and_add(vec4 *out, const vec4 *a, const vec4 *b, float scale) {
  out->x = a->x + (b->x * scale);
  out->y = a->y + (b->y * scale);
  out->z = a->z + (b->z * scale);
  out->w = a->w + (b->w * scale);
  return out;
}

float vec4_distance(const vec4 *a, const vec4 *b) {
  float dx = a->x - b->x;
  float dy = a->y - b->y;
  float dz = a->z - b->z;
  float dw = a->w - b->w;

  return sqrtf(dx * dx + dy * dy + dz * dz + dw * dw);
}

float vec4_distance_squared(const vec4 *a, const vec4 *b) {
  float dx = a->x - b->x;
  float dy = a->y - b->y;
  float dz = a->z - b->z;
  float dw = a->w - b->w;

  return dx * dx + dy * dy + dz * dz + dw * dw;
}

float vec4_length(const vec4 *a) {
  float dx = a->x;
  float dy = a->y;
  float dz = a->z;
  float dw = a->w;

  return sqrtf(dx * dx + dy * dy + dz * dz + dw * dw);
}

float vec4_length_squared(const vec4 *a) {
  float dx = a->x;
  float dy = a->y;
  float dz = a->z;
  float dw = a->w;

  return dx * dx + dy * dy + dz * dz + dw * dw;
}

vec4 *vec4_negate(vec4 *out, const vec4 *a) {
  out->x = -a->x;
  out->y = -a->y;
  out->z = -a->z;
  out->w = -a->w;
  return out;
}

vec4 *vec4_inverse(vec4 *out, const vec4 *a) {
  out->x = 1.f / a->x;
  out->y = 1.f / a->y;
  out->z = 1.f / a->z;
  out->w = 1.f / a->w;
  return out;
}

vec4 *vec4_normalize(vec4 *out, const vec4 *a) {
  float x = a->x;
  float y = a->y;
  float z = a->z;
  float w = a->w;

  float len = x * x + y * y + z * z + w * w;
  if (len > 0) {
    len = 1.f / sqrtf(len);
  }

  out->x = a->x * len;
  out->y = a->y * len;
  out->z = a->z * len;
  out->w = a->w * len;
  return out;
}

float vec4_dot(const vec4 *a, const vec4 *b) {
  return a->x * b->x + a->y * b->y + a->z * b->z + a->w * b->w;
}

vec4 *vec4_cross(vec4 *out, const vec4 *u, const vec4 *v, const vec4 *w) {
  float A = (v->x * w->y) - (v->y * w->x);
  float B = (v->x * w->z) - (v->z * w->x);
  float C = (v->x * w->w) - (v->w * w->x);
  float D = (v->y * w->z) - (v->z * w->y);
  float E = (v->y * w->w) - (v->w * w->y);
  float F = (v->z * w->w) - (v->w * w->z);

  float G = u->x;
  float H = u->y;
  float I = u->z;
  float J = u->w;

  out->x =  (H * F) - (I * E) + (J * D);
  out->y = -(G * F) + (I * C) - (J * B);
  out->z =  (G * E) - (H * C) + (J * A);
  out->w = -(G * D) + (H * B) - (I * A);
  return out;
}

vec4 *vec4_lerp(vec4 *out, const vec4 *a, const vec4 *b, float t) {
  float x = a->x;
  float y = a->y;
  float z = a->z;
  float w = a->w;

  out->x = x + t * (b->x - x);
  out->y = y + t * (b->y - y);
  out->z = z + t * (b->z - z);
  out->w = w + t * (b->z - w);
  return out;
}

vec4 *vec4_random(vec4 *out, float scale) {
  // Marsaglia, George. Choosing a Point from the Surface of a
  // Sphere. Ann. Math. Statist. 43 (1972), no. 2, 645--646.
  // http://projecteuclid.org/euclid.aoms/1177692644;
  float v1, v2, v3, v4;
  float s1, s2;

  do {
    v1 = mmath_random() * 2.f - 1.f;
    v2 = mmath_random() * 2.f - 1.f;
    s1 = v1 * v1 + v2 * v2;
  } while (s1 >= 1);

  do {
    v3 = mmath_random() * 2.f - 1.f;
    v4 = mmath_random() * 2.f - 1.f;
    s2 = v3 * v3 + v4 * v4;
  } while (s2 >= 1);

  float d = sqrtf((1 - s1) / s2);

  out->x = scale * v1;
  out->y = scale * v2;
  out->z = scale * v3 * d;
  out->w = scale * v4 * d;
  return out;
}

vec4 *vec4_transform_mat4(vec4 *out, const vec4 *a, mat4 *m) {
  float x = a->x;
  float y = a->y;
  float z = a->z;
  float w = a->w;

  out->x = m->data[0] * x + m->data[4] * y + m->data[8] * z + m->data[12] * w;
  out->y = m->data[1] * x + m->data[5] * y + m->data[9] * z + m->data[13] * w;
  out->z = m->data[2] * x + m->data[6] * y + m->data[10] * z + m->data[14] * w;
  out->w = m->data[3] * x + m->data[7] * y + m->data[11] * z + m->data[15] * w;
  return out;
}

// TODO: Quat?

bool vec4_exact_equals(const vec4 *a, const vec4 *b) {
  return a->x == b->x &&
    a->y == b->y &&
    a->z == b->z &&
    a->w == b->w
  ;
}

bool vec4_equals(const vec4 *a, const vec4 *b) {
  float a0 = a->x;
  float a1 = a->y;
  float a2 = a->z;
  float a3 = a->w;
  float b0 = b->x;
  float b1 = b->y;
  float b2 = b->z;
  float b3 = b->w;

  return (
    fabsf(a0 - b0) <= MMATH_EPSILON * fmaxf(1.f, fmaxf(fabsf(a0), fabsf(b0))) &&
    fabsf(a1 - b1) <= MMATH_EPSILON * fmaxf(1.f, fmaxf(fabsf(a1), fabsf(b1))) &&
    fabsf(a2 - b2) <= MMATH_EPSILON * fmaxf(1.f, fmaxf(fabsf(a2), fabsf(b2))) &&
    fabsf(a3 - b3) <= MMATH_EPSILON * fmaxf(1.f, fmaxf(fabsf(a3), fabsf(b3)))
  );
}
