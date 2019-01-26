#include "mmath/vec3.h"
#include "mmath_private.h"

vec3 *vec3_create() {
  vec3 *out = malloc(sizeof(vec3));
  out->x = 0.f;
  out->y = 0.f;
  out->z = 0.f;
  return out;
}

void vec3_free(vec3 *a) {
  free(a);
}

vec3 *vec3_clone(const vec3 *a) {
  vec3 *out = vec3_create();
  vec3_copy(out, a);
  return out;
}

vec3 *vec3_from_values(float x, float y, float z) {
  vec3 *out = vec3_create();
  out->x = x;
  out->y = y;
  out->z = z;
  return out;
}

vec3 *vec3_copy(vec3 *out, const vec3 *a) {
  out->x = a->x;
  out->y = a->y;
  out->z = a->z;
  return out;
}

vec3 *vec3_zero(vec3 *out) {
  return vec3_set(out, 0.f, 0.f, 0.f);
}

vec3 *vec3_set(vec3 *out, float x, float y, float z) {
  out->x = x;
  out->y = y;
  out->z = z;
  return out;
}

vec3 *vec3_add(vec3 *out, const vec3 *a, const vec3 *b) {
  out->x = a->x + b->x;
  out->y = a->y + b->y;
  out->z = a->z + b->z;
  return out;
}

vec3 *vec3_subtract(vec3 *out, const vec3 *a, const vec3 *b) {
  out->x = a->x - b->x;
  out->y = a->y - b->y;
  out->z = a->z - b->z;
  return out;
}

vec3 *vec3_multiply(vec3 *out, const vec3 *a, const vec3 *b) {
  out->x = a->x * b->x;
  out->y = a->y * b->y;
  out->z = a->z * b->z;
  return out;
}

vec3 *vec3_divide(vec3 *out, const vec3 *a, const vec3 *b) {
  out->x = a->x / b->x;
  out->y = a->y / b->y;
  out->z = a->z / b->z;
  return out;
}

vec3 *vec3_ceil(vec3 *out, const vec3 *a) {
  out->x = ceilf(a->x);
  out->y = ceilf(a->y);
  out->z = ceilf(a->z);
  return out;
}

vec3 *vec3_floor(vec3 *out, const vec3 *a) {
  out->x = floorf(a->x);
  out->y = floorf(a->y);
  out->z = floorf(a->z);
  return out;
}

vec3 *vec3_round(vec3 *out, const vec3 *a) {
  out->x = roundf(a->x);
  out->y = roundf(a->y);
  out->z = roundf(a->z);
  return out;
}

vec3 *vec3_min(vec3 *out, const vec3 *a, const vec3 *b) {
  out->x = fminf(a->x, b->x);
  out->y = fminf(a->y, b->y);
  out->z = fminf(a->z, b->z);
  return out;
}

vec3 *vec3_max(vec3 *out, const vec3 *a, const vec3 *b) {
  out->x = fmaxf(a->x, b->x);
  out->y = fmaxf(a->y, b->y);
  out->z = fmaxf(a->z, b->z);
  return out;
}

vec3 *vec3_scale(vec3 *out, const vec3 *a, float b) {
  out->x = a->x * b;
  out->y = a->y * b;
  out->z = a->z * b;
  return out;
}

vec3 *vec3_scale_and_add(vec3 *out, const vec3 *a, const vec3 *b, float scale) {
  out->x = a->x + (b->x * scale);
  out->y = a->y + (b->y * scale);
  out->z = a->z + (b->z * scale);
  return out;
}

float vec3_distance(const vec3 *a, const vec3 *b) {
  float dx = a->x - b->x;
  float dy = a->y - b->y;
  float dz = a->z - b->z;

  return sqrtf(dx * dx + dy * dy + dz * dz);
}

float vec3_distance_squared(const vec3 *a, const vec3 *b) {
  float dx = a->x - b->x;
  float dy = a->y - b->y;
  float dz = a->z - b->z;

  return dx * dx + dy * dy + dz * dz;
}

float vec3_length(const vec3 *a) {
  float dx = a->x;
  float dy = a->y;
  float dz = a->z;

  return sqrtf(dx * dx + dy * dy + dz * dz);
}

float vec3_length_squared(const vec3 *a) {
  float dx = a->x;
  float dy = a->y;
  float dz = a->z;

  return dx * dx + dy * dy + dz * dz;
}

vec3 *vec3_negate(vec3 *out, const vec3 *a) {
  out->x = -a->x;
  out->y = -a->y;
  out->z = -a->z;
  return out;
}

vec3 *vec3_inverse(vec3 *out, const vec3 *a) {
  out->x = 1.f / a->x;
  out->y = 1.f / a->y;
  out->z = 1.f / a->z;
  return out;
}

vec3 *vec3_normalize(vec3 *out, const vec3 *a) {
  float x = a->x;
  float y = a->y;
  float z = a->z;

  float len = x * x + y * y + z * z;
  if (len > 0) {
    len = 1.f / sqrtf(len);
  }

  out->x = a->x * len;
  out->y = a->y * len;
  out->z = a->z * len;
  return out;
}

float vec3_dot(const vec3 *a, const vec3 *b) {
  return a->x * b->x + a->y * b->y + a->z * b->z;
}

vec3 *vec3_cross(vec3 *out, const vec3 *a, const vec3 *b) {
  float ax = a->x;
  float ay = a->y;
  float az = a->z;
  float bx = b->x;
  float by = b->y;
  float bz = b->z;

  out->x = ay * bz - az * by;
  out->y = az * bx - ax * bz;
  out->z = ax * by - ay * bx;
  return out;
}

vec3 *vec3_lerp(vec3 *out, const vec3 *a, const vec3 *b, float t) {
  float x = a->x;
  float y = a->y;
  float z = a->z;

  out->x = x + t * (b->x - x);
  out->y = y + t * (b->y - y);
  out->z = z + t * (b->z - z);
  return out;
}

vec3 *vec3_hermite(vec3 *out, const vec3 *a, const vec3 *b, const vec3 *c, const vec3 *d, float t) {
  float factor_times2 = t * t;
  float factor1 = factor_times2 * (2 * t - 3) + 1;
  float factor2 = factor_times2 * (t - 2) + t;
  float factor3 = factor_times2 * (t - 1);
  float factor4 = factor_times2 * (3 - 2 * t);

  out->x = a->x * factor1 + b->x * factor2 + c->x * factor3 + d->x * factor4;
  out->y = a->y * factor1 + b->y * factor2 + c->y * factor3 + d->y * factor4;
  out->z = a->z * factor1 + b->z * factor2 + c->z * factor3 + d->z * factor4;
  return out;
}

vec3 *vec3_bezier(vec3 *out, const vec3 *a, const vec3 *b, const vec3 *c, const vec3 *d, float t) {
  float inverse_factor = 1 - t;
  float inverse_factor2 = inverse_factor * inverse_factor;
  float factorTimes2 = t * t;
  float factor1 = inverse_factor2 * inverse_factor;
  float factor2 = 3 * t * inverse_factor2;
  float factor3 = 3 * factorTimes2 * inverse_factor;
  float factor4 = factorTimes2 * t;

  out->x = a->x * factor1 + b->x * factor2 + c->x * factor3 + d->x * factor4;
  out->y = a->y * factor1 + b->y * factor2 + c->y * factor3 + d->y * factor4;
  out->z = a->z * factor1 + b->z * factor2 + c->z * factor3 + d->z * factor4;
  return out;
}

vec3 *vec3_random(vec3 *out, float scale) {
  float r = mmath_random() * 2.f * (float) M_PI;
  float z = (mmath_random() * 2.f) - 1.f;
  float z_scale = sqrtf(1.f - z * z) * scale;

  out->x = cosf(r) * z_scale;
  out->y = sinf(r) * z_scale;
  out->z = z * scale;
  return out;
}

vec3 *vec3_transform_mat3(vec3 *out, const vec3 *a, mat3 *m) {
  float x = a->x;
  float y = a->y;
  float z = a->z;

  out->x = x * m->data[0] + y * m->data[3] + z * m->data[6];
  out->y = x * m->data[1] + y * m->data[4] + z * m->data[7];
  out->z = x * m->data[2] + y * m->data[5] + z * m->data[8];
  return out;
}

vec3 *vec3_transform_mat4(vec3 *out, const vec3 *a, mat4 *m) {
  float x = a->x;
  float y = a->y;
  float z = a->z;

  float w = m->data[3] * x + m->data[7] * y + m->data[11] * z + m->data[15];
  if (w == 0.f) w = 1.f;
  
  out->x = (m->data[0] * x + m->data[4] * y + m->data[8] * z + m->data[12]) / w;
  out->y = (m->data[1] * x + m->data[5] * y + m->data[9] * z + m->data[13]) / w;
  out->z = (m->data[2] * x + m->data[6] * y + m->data[10] * z + m->data[14]) / w;
  return out;
}

// TODO: Quat?

vec3 *vec3_rotate_x(vec3 *out, const vec3 *a, const vec3 *b, float c) {
  vec3 p, r;

  p.x = a->x - b->x;
  p.y = a->y - b->y;
  p.z = a->z - b->z;

  float sinc = sinf(c);
  float cosc = cosf(c);

  r.x = p.x;
  r.y = p.y * cosc - p.z * sinc;
  r.z = p.y * sinc + p.z * cosc;

  out->x = r.x + b->x;
  out->y = r.y + b->y;
  out->z = r.z + b->z;
  return out;
}

vec3 *vec3_rotate_y(vec3 *out, const vec3 *a, const vec3 *b, float c) {
  vec3 p, r;

  p.x = a->x - b->x;
  p.y = a->y - b->y;
  p.z = a->z - b->z;

  float sinc = sinf(c);
  float cosc = cosf(c);

  r.x = p.z * sinc + p.x * cosc;
  r.y = p.y;
  r.z = p.z * cosc - p.x * sinc;

  out->x = r.x + b->x;
  out->y = r.y + b->y;
  out->z = r.z + b->z;
  return out;
}

vec3 *vec3_rotate_z(vec3 *out, const vec3 *a, const vec3 *b, float c) {
  vec3 p, r;

  p.x = a->x - b->x;
  p.y = a->y - b->y;
  p.z = a->z - b->z;

  float sinc = sinf(c);
  float cosc = cosf(c);

  r.x = p.x * cosc - p.y * sinc;
  r.y = p.x * sinc + p.y * cosc;
  r.z = p.z;

  out->x = r.x + b->x;
  out->y = r.y + b->y;
  out->z = r.z + b->z;
  return out;
}

float vec3_angle(const vec3 *a, const vec3 *b) {
  vec3 temp_a, temp_b;

  vec3_copy(&temp_a, a);
  vec3_copy(&temp_b, b);

  vec3_normalize(&temp_a, &temp_a);
  vec3_normalize(&temp_b, &temp_b);

  float cosine = vec3_dot(&temp_a, &temp_b);

  if (cosine > 1.f) {
    return 0.f;
  }

  if (cosine < -1.f) {
    return (float) M_PI;
  }

  return acosf(cosine);
}

bool vec3_exact_equals(const vec3 *a, const vec3 *b) {
  return a->x == b->x &&
    a->y == b->y &&
    a->z == b->z
  ;
}

bool vec3_equals(const vec3 *a, const vec3 *b) {
  float a0 = a->x;
  float a1 = a->y;
  float a2 = a->z;
  float b0 = b->x;
  float b1 = b->y;
  float b2 = b->z;

  return (
    fabsf(a0 - b0) <= MMATH_EPSILON * fmaxf(1.f, fmaxf(fabsf(a0), fabsf(b0))) &&
    fabsf(a1 - b1) <= MMATH_EPSILON * fmaxf(1.f, fmaxf(fabsf(a1), fabsf(b1))) &&
    fabsf(a2 - b2) <= MMATH_EPSILON * fmaxf(1.f, fmaxf(fabsf(a2), fabsf(b2)))
  );
}
