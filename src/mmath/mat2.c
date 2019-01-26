#include "mmath/mat2.h"
#include "mmath_private.h"

mat2 *mat2_create() {
  mat2 *out = malloc(sizeof(mat2));
  return mat2_identity(out);
}

void mat2_free(mat2 *a) {
  free(a);
}

mat2 *mat2_clone(const mat2 *a) {
  mat2 *out = mat2_create();
  mat2_copy(out, a);
  return out;
}

mat2 *mat2_from_values(float m00, float m01, float m10, float m11) {
  return mat2_set(mat2_create(), m00, m01, m10, m11);
}

mat2 *mat2_copy(mat2 *out, const mat2 *a) {
  memcpy(out->data, a->data, sizeof(a->data));
  return out;
}

mat2 *mat2_identity(mat2 *out) {
  return mat2_set(out, 1.f, 0.f, 0.f, 1.f);
}

mat2 *mat2_set(mat2 *out, float m00, float m01, float m10, float m11) {
  out->data[0] = m00;
  out->data[1] = m01;
  out->data[2] = m10;
  out->data[3] = m11;
  return out;
}

mat2 *mat2_transpose(mat2 *out, const mat2 *a) {
  if (out == a) {
    float a1 = a->data[1];
    out->data[1] = a->data[2];
    out->data[2] = a1;
  } else {
    out->data[0] = a->data[0];
    out->data[1] = a->data[2];
    out->data[2] = a->data[1];
    out->data[3] = a->data[3];
  }

  return out;
}

mat2 *mat2_invert(mat2 *out, const mat2 *a) {
  float det = mat2_determinant(a);

  if (det == 0.f) {
    return NULL;
  }

  det = 1.f / det;

  out->data[0] =  a->data[3] * det;
  out->data[1] = -a->data[1] * det;
  out->data[2] = -a->data[2] * det;
  out->data[3] =  a->data[0] * det;
  return out;
}

mat2 *mat2_adjoint(mat2 *out, const mat2 *a) {
  // Caching this value is nessecary if out == a
  float a0 = a->data[0];

  out->data[0] =  a->data[3];
  out->data[1] = -a->data[1];
  out->data[2] = -a->data[2];
  out->data[3] =  a0;
  return out;
}

float mat2_determinant(const mat2 *a) {
  return a->data[0] * a->data[3] - a->data[2] * a->data[1];
}

mat2 *mat2_multiply(mat2 *out, const mat2 *a, const mat2 *b) {
  float a0 = a->data[0];
  float a1 = a->data[1];
  float a2 = a->data[2];
  float a3 = a->data[3];
  float b0 = b->data[0];
  float b1 = b->data[1];
  float b2 = b->data[2];
  float b3 = b->data[3];

  out->data[0] = a0 * b0 + a2 * b1;
  out->data[1] = a1 * b0 + a3 * b1;
  out->data[2] = a0 * b2 + a2 * b3;
  out->data[3] = a1 * b2 + a3 * b3;
  return out;
}

mat2 *mat2_rotate(mat2 *out, const mat2 *a, float angle) {
  float a0 = a->data[0];
  float a1 = a->data[1];
  float a2 = a->data[2];
  float a3 = a->data[3];

  float s = sinf(angle);
  float c = cosf(angle);

  out->data[0] = a0 *  c + a2 * s;
  out->data[1] = a1 *  c + a3 * s;
  out->data[2] = a0 * -s + a2 * c;
  out->data[3] = a1 * -s + a3 * c;
  return out;
}

mat2 *mat2_scale(mat2 *out, const mat2 *a, const vec2 *v) {
  float a0 = a->data[0];
  float a1 = a->data[1];
  float a2 = a->data[2];
  float a3 = a->data[3];
  float v0 = v->data[0];
  float v1 = v->data[1];

  out->data[0] = a0 * v0;
  out->data[1] = a1 * v0;
  out->data[2] = a2 * v1;
  out->data[3] = a3 * v1;
  return out;
}

mat2 *mat2_from_rotation(mat2 *out, float angle) {
  float s = sinf(angle);
  float c = cosf(angle);

  out->data[0] =  c;
  out->data[1] =  s;
  out->data[2] = -s;
  out->data[3] =  c;
  return out;
}

mat2 *mat2_from_scaling(mat2 *out, const vec2 *v) {
  out->data[0] = v->data[0];
  out->data[1] = 0;
  out->data[2] = 0;
  out->data[3] = v->data[1];
  return out;
}

float mat2_frob(const mat2 *a) {
  float a0 = a->data[0];
  float a1 = a->data[1];
  float a2 = a->data[2];
  float a3 = a->data[3];

  return sqrtf(a0 * a0 + a1 * a1 + a2 * a2 + a3 * a3);
}

mat2 *mat2_add(mat2 *out, const mat2 *a, const mat2 *b) {
  out->data[0] = a->data[0] + b->data[0];
  out->data[1] = a->data[1] + b->data[1];
  out->data[2] = a->data[2] + b->data[2];
  out->data[3] = a->data[3] + b->data[3];

  return out;
}

mat2 *mat2_subtract(mat2 *out, const mat2 *a, const mat2 *b) {
  out->data[0] = a->data[0] - b->data[0];
  out->data[1] = a->data[1] - b->data[1];
  out->data[2] = a->data[2] - b->data[2];
  out->data[3] = a->data[3] - b->data[3];

  return out;
}

mat2 *mat2_multiply_scalar(mat2 *out, const mat2 *a, float scale) {
  out->data[0] = a->data[0] * scale;
  out->data[1] = a->data[1] * scale;
  out->data[2] = a->data[2] * scale;
  out->data[3] = a->data[3] * scale;

  return out;
}

mat2 *mat2_multiply_scalar_and_add(mat2 *out, const mat2 *a, const mat2 *b, float scale) {
  out->data[0] = a->data[0] + (b->data[0] * scale);
  out->data[1] = a->data[1] + (b->data[1] * scale);
  out->data[2] = a->data[2] + (b->data[2] * scale);
  out->data[3] = a->data[3] + (b->data[3] * scale);

  return out;
}

bool mat2_exact_equals(const mat2 *a, const mat2 *b) {
  return (
    a->data[0] == b->data[0] &&
    a->data[1] == b->data[1] &&
    a->data[2] == b->data[2] &&
    a->data[3] == b->data[3]
  );
}

bool mat2_equals(const mat2 *a, const mat2 *b) {
  float a0 = a->data[0];
  float a1 = a->data[1];
  float a2 = a->data[2];
  float a3 = a->data[3];
  float b0 = b->data[0];
  float b1 = b->data[1];
  float b2 = b->data[2];
  float b3 = b->data[3];

  return (
    fabsf(a0 - b0) <= MMATH_EPSILON * fmaxf(1.0f, fmaxf(fabsf(a0), fabsf(b0))) &&
    fabsf(a1 - b1) <= MMATH_EPSILON * fmaxf(1.0f, fmaxf(fabsf(a1), fabsf(b1))) &&
    fabsf(a2 - b2) <= MMATH_EPSILON * fmaxf(1.0f, fmaxf(fabsf(a2), fabsf(b2))) &&
    fabsf(a3 - b3) <= MMATH_EPSILON * fmaxf(1.0f, fmaxf(fabsf(a3), fabsf(b3)))
  );
}
