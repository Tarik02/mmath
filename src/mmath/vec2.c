#include "mmath/vec2.h"
#include "mmath_private.h"

vec2 *vec2_create() {
  vec2 *out = malloc(sizeof(vec2));
  out->x = 0.f;
  out->y = 0.f;
  return out;
}

void vec2_free(vec2 *a) {
  free(a);
}

vec2 *vec2_clone(const vec2 *a) {
  vec2 *out = vec2_create();
  vec2_copy(out, a);
  return out;
}

vec2 *vec2_from_values(float x, float y) {
  vec2 *out = vec2_create();
  out->x = x;
  out->y = y;
  return out;
}

vec2 *vec2_copy(vec2 *out, const vec2 *a) {
  out->x = a->x;
  out->y = a->y;
  return out;
}

vec2 *vec2_zero(vec2 *out) {
  return vec2_set(out, 0.f, 0.f);
}

vec2 *vec2_set(vec2 *out, float x, float y) {
  out->x = x;
  out->y = y;
  return out;
}

vec2 *vec2_add(vec2 *out, const vec2 *a, const vec2 *b) {
  out->x = a->x + b->x;
  out->y = a->y + b->y;
  return out;
}

vec2 *vec2_subtract(vec2 *out, const vec2 *a, const vec2 *b) {
  out->x = a->x - b->x;
  out->y = a->y - b->y;
  return out;
}

vec2 *vec2_multiply(vec2 *out, const vec2 *a, const vec2 *b) {
  out->x = a->x * b->x;
  out->y = a->y * b->y;
  return out;
}

vec2 *vec2_divide(vec2 *out, const vec2 *a, const vec2 *b) {
  out->x = a->x / b->x;
  out->y = a->y / b->y;
  return out;
}

vec2 *vec2_ceil(vec2 *out, const vec2 *a) {
  out->x = ceilf(a->x);
  out->y = ceilf(a->y);
  return out;
}

vec2 *vec2_floor(vec2 *out, const vec2 *a) {
  out->x = floorf(a->x);
  out->y = floorf(a->y);
  return out;
}

vec2 *vec2_round(vec2 *out, const vec2 *a) {
  out->x = roundf(a->x);
  out->y = roundf(a->y);
  return out;
}

vec2 *vec2_min(vec2 *out, const vec2 *a, const vec2 *b) {
  out->x = fminf(a->x, b->x);
  out->y = fminf(a->y, b->y);
  return out;
}

vec2 *vec2_max(vec2 *out, const vec2 *a, const vec2 *b) {
  out->x = fmaxf(a->x, b->x);
  out->y = fmaxf(a->y, b->y);
  return out;
}

vec2 *vec2_scale(vec2 *out, const vec2 *a, float b) {
  out->x = a->x * b;
  out->y = a->y * b;
  return out;
}

vec2 *vec2_scale_and_add(vec2 *out, const vec2 *a, const vec2 *b, float scale) {
  out->x = a->x + (b->x * scale);
  out->y = a->y + (b->y * scale);
  return out;
}

float vec2_distance(const vec2 *a, const vec2 *b) {
  float dx = a->x - b->x;
  float dy = a->y - b->y;

  return sqrtf(dx * dx + dy * dy);
}

float vec2_distance_squared(const vec2 *a, const vec2 *b) {
  float dx = a->x - b->x;
  float dy = a->y - b->y;

  return dx * dx + dy * dy;
}

float vec2_length(const vec2 *a) {
  float dx = a->x;
  float dy = a->y;

  return sqrtf(dx * dx + dy * dy);
}

float vec2_length_squared(const vec2 *a) {
  float dx = a->x;
  float dy = a->y;

  return dx * dx + dy * dy;
}

vec2 *vec2_negate(vec2 *out, const vec2 *a) {
  out->x = -a->x;
  out->y = -a->y;
  return out;
}

vec2 *vec2_inverse(vec2 *out, const vec2 *a) {
  out->x = 1.f / a->x;
  out->y = 1.f / a->y;
  return out;
}

vec2 *vec2_normalize(vec2 *out, const vec2 *a) {
  float x = a->x;
  float y = a->y;

  float len = x * x + y * y;
  if (len > 0) {
    len = 1.f / sqrtf(len);
  }

  out->x = a->x * len;
  out->y = a->y * len;
  return out;
}

float vec2_dot(const vec2 *a, const vec2 *b) {
  return a->x * b->x + a->y * b->y;
}

vec3 *vec2_cross(vec3 *out, const vec2 *a, const vec2 *b) {
  float z = a->x * b->y - a->y * b->x;
  out->x = out->y = 0;
  out->z = z;
  return out;
}

vec2 *vec2_lerp(vec2 *out, const vec2 *a, const vec2 *b, float t) {
  float x = a->x;
  float y = a->y;

  out->x = x + t * (b->x - x);
  out->y = y + t * (b->y - y);
  return out;
}

vec2 *vec2_random(vec2 *out, float scale) {
  float r = mmath_random() * 2.f * (float) M_PI;

  out->x = cosf(r) * scale;
  out->y = sinf(r) * scale;
  return out;
}

vec2 *vec2_transform_mat2(vec2 *out, const vec2 *a, const mat2 *m) {
  float x = a->x;
  float y = a->y;

  out->x = m->data[0] * x + m->data[2] * y;
  out->y = m->data[1] * x + m->data[3] * y;
  return out;
}

vec2 *vec2_transform_mat2d(vec2 *out, const vec2 *a, const mat2d *m) {
  float x = a->x;
  float y = a->y;

  out->x = m->data[0] * x + m->data[2] * y + m->data[4];
  out->y = m->data[1] * x + m->data[3] * y + m->data[5];
  return out;
}

vec2 *vec2_transform_mat3(vec2 *out, const vec2 *a, const mat3 *m) {
  float x = a->x;
  float y = a->y;

  out->x = m->data[0] * x + m->data[3] * y + m->data[6];
  out->y = m->data[1] * x + m->data[4] * y + m->data[7];
  return out;
}

vec2 *vec2_transform_mat4(vec2 *out, const vec2 *a, const mat4 *m) {
  float x = a->x;
  float y = a->y;

  out->x = m->data[0] * x + m->data[4] * y + m->data[12];
  out->y = m->data[1] * x + m->data[5] * y + m->data[13];
  return out;
}

vec2 *vec2_rotate(vec2 *out, const vec2 *a, const vec2 *b, float c) {
  float dx = a->x - b->x;
  float dy = a->y - b->y;

  float sinc = sinf(c);
  float cosc = cosf(c);

  out->x = dx * cosc - dy * sinc + b->x;
  out->y = dx * sinc + dy * cosc + b->y;
  return out;
}

float vec2_angle(const vec2 *a, const vec2 *b) {
  float x1 = a->x;
  float y1 = a->y;
  float x2 = b->x;
  float y2 = b->y;

  float len1 = x1 * x1 + y1 * y1;
  if (len1 > 0) {
    len1 = 1 / sqrtf(len1);
  }

  float len2 = x2 * x2 + y2 * y2;
  if (len2 > 0) {
    len2 = 1 / sqrtf(len2);
  }

  float cosine = (x1 * x2 + y1 * y2) * len1 * len2;

  if (cosine > 1.f) {
    return 0;
  }

  if (cosine < -1.f) {
    return (float) M_PI;
  }

  return acosf(cosine);
}

bool vec2_exact_equals(const vec2 *a, const vec2 *b) {
  return a->x == b->x && a->y == b->y;
}

bool vec2_equals(const vec2 *a, const vec2 *b) {
  float a0 = a->x;
  float a1 = a->y;
  float b0 = b->x;
  float b1 = b->y;

  return (
    fabsf(a0 - b0) <= MMATH_EPSILON * fmaxf(1.f, fmaxf(fabsf(a0), fabsf(b0))) &&
    fabsf(a1 - b1) <= MMATH_EPSILON * fmaxf(1.f, fmaxf(fabsf(a1), fabsf(b1)))
  );
}
