#include "mmath/mat2d.h"
#include "mmath_private.h"

mat2d *mat2d_create() {
  mat2d *out = malloc(sizeof(mat2d));
  return mat2d_identity(out);
}

void mat2d_free(mat2d *a) {
  free(a);
}

mat2d *mat2d_clone(const mat2d *a) {
  mat2d *out = mat2d_create();
  mat2d_copy(out, a);
  return out;
}

mat2d *mat2d_from_values(float a, float b, float c, float d, float tx, float ty) {
  return mat2d_set(mat2d_create(), a, b, c, d, tx, ty);
}

mat2d *mat2d_copy(mat2d *out, const mat2d *a) {
  memcpy(out->data, a->data, sizeof(a->data));
  return out;
}

mat2d *mat2d_identity(mat2d *out) {
  return mat2d_set(out, 1.f, 0.f, 0.f, 1.f, 0.f, 0.f);
}

mat2d *mat2d_set(mat2d *out, float a, float b, float c, float d, float tx, float ty) {
  out->a = a;
  out->b = b;
  out->c = c;
  out->d = d;
  out->tx = tx;
  out->ty = ty;
  return out;
}

mat2d *mat2d_invert(mat2d *out, const mat2d *a) {
  float det = mat2d_determinant(a);

  if (det == 0.f) {
    return NULL;
  }

  det = 1.f / det;

  out->data[0] =  a->d * det;
  out->data[1] = -a->b * det;
  out->data[2] = -a->c * det;
  out->data[3] =  a->a * det;
  out->data[4] = (a->c * a->ty - a->d * a->tx) * det;
  out->data[5] = (a->b * a->tx - a->a * a->ty) * det;
  return out;
}

float mat2d_determinant(const mat2d *a) {
  return a->data[0] * a->data[3] - a->data[2] * a->data[1];
}

mat2d *mat2d_multiply(mat2d *out, const mat2d *a, const mat2d *b) {
  float a0 = a->data[0];
  float a1 = a->data[1];
  float a2 = a->data[2];
  float a3 = a->data[3];
  float a4 = a->data[4];
  float a5 = a->data[5];
  float b0 = b->data[0];
  float b1 = b->data[1];
  float b2 = b->data[2];
  float b3 = b->data[3];
  float b4 = b->data[4];
  float b5 = b->data[5];

  out->data[0] = a0 * b0 + a2 * b1;
  out->data[1] = a1 * b0 + a3 * b1;
  out->data[2] = a0 * b2 + a2 * b3;
  out->data[3] = a1 * b2 + a3 * b3;
  out->data[4] = a0 * b4 + a2 * b5 + a4;
  out->data[5] = a1 * b4 + a3 * b5 + a5;
  return out;
}

mat2d *mat2d_rotate(mat2d *out, const mat2d *a, float angle) {
  float a0 = a->data[0];
  float a1 = a->data[1];
  float a2 = a->data[2];
  float a3 = a->data[3];
  float a4 = a->data[4];
  float a5 = a->data[5];

  float s = sinf(angle);
  float c = cosf(angle);

  out->data[0] = a0 *  c + a2 * s;
  out->data[1] = a1 *  c + a3 * s;
  out->data[2] = a0 * -s + a2 * c;
  out->data[3] = a1 * -s + a3 * c;
  out->data[4] = a4;
  out->data[5] = a5;
  return out;
}

mat2d *mat2d_scale(mat2d *out, const mat2d *a, const vec2 *v) {
  float a0 = a->data[0];
  float a1 = a->data[1];
  float a2 = a->data[2];
  float a3 = a->data[3];
  float a4 = a->data[4];
  float a5 = a->data[5];
  float v0 = v->data[0];
  float v1 = v->data[1];

  out->data[0] = a0 * v0;
  out->data[1] = a1 * v0;
  out->data[2] = a2 * v1;
  out->data[3] = a3 * v1;
  out->data[4] = a4;
  out->data[5] = a5;
  return out;
}

mat2d *mat2d_translate(mat2d *out, const mat2d *a, const vec2 *v) {
  float a0 = a->data[0];
  float a1 = a->data[1];
  float a2 = a->data[2];
  float a3 = a->data[3];
  float a4 = a->data[4];
  float a5 = a->data[5];
  float v0 = v->data[0];
  float v1 = v->data[1];

  out->data[0] = a0;
  out->data[1] = a1;
  out->data[2] = a2;
  out->data[3] = a3;
  out->data[4] = a0 * v0 + a2 * v1 + a4;
  out->data[5] = a1 * v0 + a3 * v1 + a5;
  return out;
}

mat2d *mat2d_from_rotation(mat2d *out, float angle) {
  float s = sinf(angle);
  float c = cosf(angle);

  out->data[0] =  c;
  out->data[1] =  s;
  out->data[2] = -s;
  out->data[3] =  c;
  out->data[4] =  0;
  out->data[5] =  0;
  return out;
}

mat2d *mat2d_from_scaling(mat2d *out, const vec2 *v) {
  out->data[0] = v->data[0];
  out->data[1] = 0;
  out->data[2] = 0;
  out->data[3] = v->data[1];
  out->data[4] = 0;
  out->data[5] = 0;
  return out;
}

mat2d *mat2d_from_translation(mat2d *out, const vec2 *v) {
  out->data[0] = 1;
  out->data[1] = 0;
  out->data[2] = 0;
  out->data[3] = 1;
  out->data[4] = v->data[0];
  out->data[5] = v->data[1];
  return out;
}

float mat2d_frob(const mat2d *a) {
  float a0 = a->data[0];
  float a1 = a->data[1];
  float a2 = a->data[2];
  float a3 = a->data[3];
  float a4 = a->data[4];
  float a5 = a->data[5];

  return sqrtf(a0 * a0 + a1 * a1 + a2 * a2 + a3 * a3 + a4 * a4 + a5 * a5 + 1);
}

mat2d *mat2d_add(mat2d *out, const mat2d *a, const mat2d *b) {
  out->data[0] = a->data[0] + b->data[0];
  out->data[1] = a->data[1] + b->data[1];
  out->data[2] = a->data[2] + b->data[2];
  out->data[3] = a->data[3] + b->data[3];
  out->data[4] = a->data[4] + b->data[4];
  out->data[5] = a->data[5] + b->data[5];

  return out;
}

mat2d *mat2d_subtract(mat2d *out, const mat2d *a, const mat2d *b) {
  out->data[0] = a->data[0] - b->data[0];
  out->data[1] = a->data[1] - b->data[1];
  out->data[2] = a->data[2] - b->data[2];
  out->data[3] = a->data[3] - b->data[3];
  out->data[4] = a->data[4] - b->data[4];
  out->data[5] = a->data[5] - b->data[5];

  return out;
}

mat2d *mat2d_multiply_scalar(mat2d *out, const mat2d *a, float scale) {
  out->data[0] = a->data[0] * scale;
  out->data[1] = a->data[1] * scale;
  out->data[2] = a->data[2] * scale;
  out->data[3] = a->data[3] * scale;
  out->data[4] = a->data[4] * scale;
  out->data[5] = a->data[5] * scale;

  return out;
}

mat2d *mat2d_multiply_scalar_and_add(mat2d *out, const mat2d *a, const mat2d *b, float scale) {
  out->data[0] = a->data[0] + (b->data[0] * scale);
  out->data[1] = a->data[1] + (b->data[1] * scale);
  out->data[2] = a->data[2] + (b->data[2] * scale);
  out->data[3] = a->data[3] + (b->data[3] * scale);
  out->data[4] = a->data[4] + (b->data[4] * scale);
  out->data[5] = a->data[5] + (b->data[5] * scale);

  return out;
}

bool mat2d_exact_equals(const mat2d *a, const mat2d *b) {
  return (
    a->data[0] == b->data[0] &&
    a->data[1] == b->data[1] &&
    a->data[2] == b->data[2] &&
    a->data[3] == b->data[3] &&
    a->data[4] == b->data[4] &&
    a->data[5] == b->data[5]
  );
}

bool mat2d_equals(const mat2d *a, const mat2d *b) {
  float a0 = a->data[0];
  float a1 = a->data[1];
  float a2 = a->data[2];
  float a3 = a->data[3];
  float a4 = a->data[4];
  float a5 = a->data[5];
  float b0 = b->data[0];
  float b1 = b->data[1];
  float b2 = b->data[2];
  float b3 = b->data[3];
  float b4 = b->data[4];
  float b5 = b->data[5];

  return (
    fabsf(a0 - b0) <= MMATH_EPSILON * fmaxf(1.0f, fmaxf(fabsf(a0), fabsf(b0))) &&
    fabsf(a1 - b1) <= MMATH_EPSILON * fmaxf(1.0f, fmaxf(fabsf(a1), fabsf(b1))) &&
    fabsf(a2 - b2) <= MMATH_EPSILON * fmaxf(1.0f, fmaxf(fabsf(a2), fabsf(b2))) &&
    fabsf(a3 - b3) <= MMATH_EPSILON * fmaxf(1.0f, fmaxf(fabsf(a3), fabsf(b3))) &&
    fabsf(a4 - b4) <= MMATH_EPSILON * fmaxf(1.0f, fmaxf(fabsf(a4), fabsf(b4))) &&
    fabsf(a5 - b5) <= MMATH_EPSILON * fmaxf(1.0f, fmaxf(fabsf(a5), fabsf(b5)))
  );
}
