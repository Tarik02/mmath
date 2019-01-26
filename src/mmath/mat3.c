#include "mmath/mat3.h"
#include "mmath_private.h"

mat3 *mat3_create() {
  mat3 *out = malloc(sizeof(mat3));
  return mat3_identity(out);
}

void mat3_free(mat3 *a) {
  free(a);
}

mat3 *mat3_clone(const mat3 *a) {
  mat3 *out = mat3_create();
  mat3_copy(out, a);
  return out;
}

mat3 *mat3_from_values(
  float m00,
  float m01,
  float m02,
  float m10,
  float m11,
  float m12,
  float m20,
  float m21,
  float m22
) {
  return mat3_set(mat3_create(), m00, m01, m02, m10, m11, m12, m20, m21, m22);
}

mat3 *mat3_copy(mat3 *out, const mat3 *a) {
  memcpy(out->data, a->data, sizeof(a->data));
  return out;
}

mat3 *mat3_identity(mat3 *out) {
  return mat3_set(out, 1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f);
}

mat3 *mat3_set(
  mat3 *out,
  float m00,
  float m01,
  float m02,
  float m10,
  float m11,
  float m12,
  float m20,
  float m21,
  float m22
) {
  out->m00 = m00;
  out->m01 = m01;
  out->m02 = m02;
  out->m10 = m10;
  out->m11 = m11;
  out->m12 = m12;
  out->m20 = m20;
  out->m21 = m21;
  out->m22 = m22;
  return out;
}

mat3 *mat3_transpose(mat3 *out, const mat3 *a) {
  if (out == a) {
    float a01 = a->m01;
    float a02 = a->m02;
    float a12 = a->m12;

    out->data[1] = a->data[3];
    out->data[2] = a->data[6];
    out->data[3] = a01;
    out->data[5] = a->data[7];
    out->data[6] = a02;
    out->data[7] = a12;
  } else {
    out->data[0] = a->data[0];
    out->data[1] = a->data[3];
    out->data[2] = a->data[6];
    out->data[3] = a->data[1];
    out->data[4] = a->data[4];
    out->data[5] = a->data[7];
    out->data[6] = a->data[2];
    out->data[7] = a->data[5];
    out->data[8] = a->data[8];
  }

  return out;
}

mat3 *mat3_invert(mat3 *out, const mat3 *a) {
  float a00 = a->m00;
  float a01 = a->m01;
  float a02 = a->m02;
  float a10 = a->m10;
  float a11 = a->m11;
  float a12 = a->m12;
  float a20 = a->m20;
  float a21 = a->m21;
  float a22 = a->m22;

  float b01 = a22 * a11 - a12 * a21;
  float b11 = -a22 * a10 + a12 * a20;
  float b21 = a21 * a10 - a11 * a20;

  float det = mat3_determinant(a);

  if (det == 0.f) {
    return NULL;
  }

  det = 1.f / det;

  out->data[0] = b01 * det;
  out->data[1] = (-a22 * a01 + a02 * a21) * det;
  out->data[2] = (a12 * a01 - a02 * a11) * det;
  out->data[3] = b11 * det;
  out->data[4] = (a22 * a00 - a02 * a20) * det;
  out->data[5] = (-a12 * a00 + a02 * a10) * det;
  out->data[6] = b21 * det;
  out->data[7] = (-a21 * a00 + a01 * a20) * det;
  out->data[8] = (a11 * a00 - a01 * a10) * det;
  return out;
}

mat3 *mat3_adjoint(mat3 *out, const mat3 *a) {
  float a00 = a->m00;
  float a01 = a->m01;
  float a02 = a->m02;
  float a10 = a->m10;
  float a11 = a->m11;
  float a12 = a->m12;
  float a20 = a->m20;
  float a21 = a->m21;
  float a22 = a->m22;

  out->data[0] = (a11 * a22 - a12 * a21);
  out->data[1] = (a02 * a21 - a01 * a22);
  out->data[2] = (a01 * a12 - a02 * a11);
  out->data[3] = (a12 * a20 - a10 * a22);
  out->data[4] = (a00 * a22 - a02 * a20);
  out->data[5] = (a02 * a10 - a00 * a12);
  out->data[6] = (a10 * a21 - a11 * a20);
  out->data[7] = (a01 * a20 - a00 * a21);
  out->data[8] = (a00 * a11 - a01 * a10);
  return out;
}

float mat3_determinant(const mat3 *a) {
  float a00 = a->m00;
  float a01 = a->m01;
  float a02 = a->m02;
  float a10 = a->m10;
  float a11 = a->m11;
  float a12 = a->m12;
  float a20 = a->m20;
  float a21 = a->m21;
  float a22 = a->m22;

  return a00 * (a22 * a11 - a12 * a21) + a01 * (-a22 * a10 + a12 * a20) + a02 * (a21 * a10 - a11 * a20);
}

mat3 *mat3_multiply(mat3 *out, const mat3 *a, const mat3 *b) {
  float a00 = a->m00;
  float a01 = a->m01;
  float a02 = a->m02;
  float a10 = a->m10;
  float a11 = a->m11;
  float a12 = a->m12;
  float a20 = a->m20;
  float a21 = a->m21;
  float a22 = a->m22;

  float b00 = b->m00;
  float b01 = b->m01;
  float b02 = b->m02;
  float b10 = b->m10;
  float b11 = b->m11;
  float b12 = b->m12;
  float b20 = b->m20;
  float b21 = b->m21;
  float b22 = b->m22;

  out->data[0] = b00 * a00 + b01 * a10 + b02 * a20;
  out->data[1] = b00 * a01 + b01 * a11 + b02 * a21;
  out->data[2] = b00 * a02 + b01 * a12 + b02 * a22;
  
  out->data[3] = b10 * a00 + b11 * a10 + b12 * a20;
  out->data[4] = b10 * a01 + b11 * a11 + b12 * a21;
  out->data[5] = b10 * a02 + b11 * a12 + b12 * a22;
  
  out->data[6] = b20 * a00 + b21 * a10 + b22 * a20;
  out->data[7] = b20 * a01 + b21 * a11 + b22 * a21;
  out->data[8] = b20 * a02 + b21 * a12 + b22 * a22;

  return out;
}

mat3 *mat3_translate(mat3 *out, const mat3 *a, const vec2 *v) {
  float a00 = a->m00;
  float a01 = a->m01;
  float a02 = a->m02;
  float a10 = a->m10;
  float a11 = a->m11;
  float a12 = a->m12;
  float a20 = a->m20;
  float a21 = a->m21;
  float a22 = a->m22;
  float x = v->x;
  float y = v->y;

  out->data[0] = a00;
  out->data[1] = a01;
  out->data[2] = a02;
  
  out->data[3] = a10;
  out->data[4] = a11;
  out->data[5] = a12;
  
  out->data[6] = x * a00 + y * a10 + a20;
  out->data[7] = x * a01 + y * a11 + a21;
  out->data[8] = x * a02 + y * a12 + a22;

  return out;
}

mat3 *mat3_rotate(mat3 *out, const mat3 *a, float angle) {
  float a00 = a->m00;
  float a01 = a->m01;
  float a02 = a->m02;
  float a10 = a->m10;
  float a11 = a->m11;
  float a12 = a->m12;
  float a20 = a->m20;
  float a21 = a->m21;
  float a22 = a->m22;
  float s = sinf(angle);
  float c = cosf(angle);

  out->data[0] = c * a00 + s * a10;
  out->data[1] = c * a01 + s * a11;
  out->data[2] = c * a02 + s * a12;

  out->data[3] = c * a10 - s * a00;
  out->data[4] = c * a11 - s * a01;
  out->data[5] = c * a12 - s * a02;

  out->data[6] = a20;
  out->data[7] = a21;
  out->data[8] = a22;

  return out;
}

mat3 *mat3_scale(mat3 *out, const mat3 *a, const vec2 *v) {
  float x = v->x;
  float y = v->y;

  out->data[0] = x * a->data[0];
  out->data[1] = x * a->data[1];
  out->data[2] = x * a->data[2];

  out->data[3] = y * a->data[3];
  out->data[4] = y * a->data[4];
  out->data[5] = y * a->data[5];

  out->data[6] = a->data[6];
  out->data[7] = a->data[7];
  out->data[8] = a->data[8];

  return out;
}

mat3 *mat3_from_translation(mat3 *out, const vec2 *v) {
  out->data[0] = 1;
  out->data[1] = 0;
  out->data[2] = 0;
  out->data[3] = 0;
  out->data[4] = 1;
  out->data[5] = 0;
  out->data[6] = v->x;
  out->data[7] = v->y;
  out->data[8] = 1;
  return out;
}

mat3 *mat3_from_rotation(mat3 *out, float angle) {
  float s = sinf(angle);
  float c = cosf(angle);

  out->data[0] = c;
  out->data[1] = s;
  out->data[2] = 0;

  out->data[3] = -s;
  out->data[4] = c;
  out->data[5] = 0;

  out->data[6] = 0;
  out->data[7] = 0;
  out->data[8] = 1;

  return out;
}

mat3 *mat3_from_scaling(mat3 *out, const vec2 *v) {
  out->data[0] = v->x;
  out->data[1] = 0;
  out->data[2] = 0;

  out->data[3] = 0;
  out->data[4] = v->y;
  out->data[5] = 0;

  out->data[6] = 0;
  out->data[7] = 0;
  out->data[8] = 1;

  return out;
}

mat3 *mat3_from_mat2d(mat3 *out, const mat2d *a) {
  out->data[0] = a->data[0];
  out->data[1] = a->data[1];
  out->data[2] = 0;

  out->data[3] = a->data[2];
  out->data[4] = a->data[3];
  out->data[5] = 0;

  out->data[6] = a->data[4];
  out->data[7] = a->data[5];
  out->data[8] = 1;

  return out;
}

mat3 *mat3_from_mat4(mat3 *out, const mat4 *a) {
  out->data[0] = a->data[0];
  out->data[1] = a->data[1];
  out->data[2] = a->data[2];
  out->data[3] = a->data[4];
  out->data[4] = a->data[5];
  out->data[5] = a->data[6];
  out->data[6] = a->data[8];
  out->data[7] = a->data[9];
  out->data[8] = a->data[10];
  return out;
}

float mat3_frob(const mat3 *a) {
  float a0 = a->data[0];
  float a1 = a->data[1];
  float a2 = a->data[2];
  float a3 = a->data[3];
  float a4 = a->data[4];
  float a5 = a->data[5];
  float a6 = a->data[6];
  float a7 = a->data[7];
  float a8 = a->data[8];

  return sqrtf(
    a0 * a0 +
    a1 * a1 +
    a2 * a2 +
    a3 * a3 +
    a4 * a4 +
    a5 * a5 +
    a6 * a6 +
    a7 * a7 +
    a8 * a8
  );
}

mat3 *mat3_add(mat3 *out, const mat3 *a, const mat3 *b) {
  out->data[0] = a->data[0] + b->data[0];
  out->data[1] = a->data[1] + b->data[1];
  out->data[2] = a->data[2] + b->data[2];
  out->data[3] = a->data[3] + b->data[3];
  out->data[4] = a->data[4] + b->data[4];
  out->data[5] = a->data[5] + b->data[5];
  out->data[6] = a->data[6] + b->data[6];
  out->data[7] = a->data[7] + b->data[7];
  out->data[8] = a->data[8] + b->data[8];

  return out;
}

mat3 *mat3_subtract(mat3 *out, const mat3 *a, const mat3 *b) {
  out->data[0] = a->data[0] - b->data[0];
  out->data[1] = a->data[1] - b->data[1];
  out->data[2] = a->data[2] - b->data[2];
  out->data[3] = a->data[3] - b->data[3];
  out->data[4] = a->data[4] - b->data[4];
  out->data[5] = a->data[5] - b->data[5];
  out->data[6] = a->data[6] - b->data[6];
  out->data[7] = a->data[7] - b->data[7];
  out->data[8] = a->data[8] - b->data[8];

  return out;
}

mat3 *mat3_multiply_scalar(mat3 *out, const mat3 *a, float scale) {
  out->data[0] = a->data[0] * scale;
  out->data[1] = a->data[1] * scale;
  out->data[2] = a->data[2] * scale;
  out->data[3] = a->data[3] * scale;
  out->data[4] = a->data[4] * scale;
  out->data[5] = a->data[5] * scale;
  out->data[6] = a->data[6] * scale;
  out->data[7] = a->data[7] * scale;
  out->data[8] = a->data[8] * scale;

  return out;
}

mat3 *mat3_multiply_scalar_and_add(mat3 *out, const mat3 *a, const mat3 *b, float scale) {
  out->data[0] = a->data[0] * (b->data[0] * scale);
  out->data[1] = a->data[1] * (b->data[1] * scale);
  out->data[2] = a->data[2] * (b->data[2] * scale);
  out->data[3] = a->data[3] * (b->data[3] * scale);
  out->data[4] = a->data[4] * (b->data[4] * scale);
  out->data[5] = a->data[5] * (b->data[5] * scale);
  out->data[6] = a->data[6] * (b->data[6] * scale);
  out->data[7] = a->data[7] * (b->data[7] * scale);
  out->data[8] = a->data[8] * (b->data[8] * scale);

  return out;
}

mat3 *mat3_projection(mat3 *out, float width, float height) {
  out->data[0] = 2.f / width;
  out->data[1] = 0.f;
  out->data[2] = 0.f;
  out->data[3] = 0.f;
  out->data[4] = -2.f / height;
  out->data[5] = 0.f;
  out->data[6] = -1.f;
  out->data[7] = 1.f;
  out->data[8] = 1.f;
  return out;
}

bool mat3_exact_equals(const mat3 *a, const mat3 *b) {
  return (
    a->data[0] == b->data[0] &&
    a->data[1] == b->data[1] &&
    a->data[2] == b->data[2] &&
    a->data[3] == b->data[3] &&
    a->data[4] == b->data[4] &&
    a->data[5] == b->data[5] &&
    a->data[6] == b->data[6] &&
    a->data[7] == b->data[7] &&
    a->data[8] == b->data[8]
  );
}

bool mat3_equals(const mat3 *a, const mat3 *b) {
  float a0 = a->data[0];
  float a1 = a->data[1];
  float a2 = a->data[2];
  float a3 = a->data[3];
  float a4 = a->data[4];
  float a5 = a->data[5];
  float a6 = a->data[6];
  float a7 = a->data[7];
  float a8 = a->data[8];
  float b0 = b->data[0];
  float b1 = b->data[1];
  float b2 = b->data[2];
  float b3 = b->data[3];
  float b4 = b->data[4];
  float b5 = b->data[5];
  float b6 = b->data[6];
  float b7 = b->data[7];
  float b8 = b->data[8];

  return (
    fabsf(a0 - b0) <= MMATH_EPSILON * fmaxf(1.f, fmaxf(fabsf(a0), fabsf(b0))) &&
    fabsf(a1 - b1) <= MMATH_EPSILON * fmaxf(1.f, fmaxf(fabsf(a1), fabsf(b1))) &&
    fabsf(a2 - b2) <= MMATH_EPSILON * fmaxf(1.f, fmaxf(fabsf(a2), fabsf(b2))) &&
    fabsf(a3 - b3) <= MMATH_EPSILON * fmaxf(1.f, fmaxf(fabsf(a3), fabsf(b3))) &&
    fabsf(a4 - b4) <= MMATH_EPSILON * fmaxf(1.f, fmaxf(fabsf(a4), fabsf(b4))) &&
    fabsf(a5 - b5) <= MMATH_EPSILON * fmaxf(1.f, fmaxf(fabsf(a5), fabsf(b5))) &&
    fabsf(a6 - b6) <= MMATH_EPSILON * fmaxf(1.f, fmaxf(fabsf(a6), fabsf(b6))) &&
    fabsf(a7 - b7) <= MMATH_EPSILON * fmaxf(1.f, fmaxf(fabsf(a7), fabsf(b7))) &&
    fabsf(a8 - b8) <= MMATH_EPSILON * fmaxf(1.f, fmaxf(fabsf(a8), fabsf(b8)))
  );
}
