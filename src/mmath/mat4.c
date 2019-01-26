#include "mmath/mat4.h"
#include "mmath_private.h"

mat4 *mat4_create() {
  mat4 *out = malloc(sizeof(mat4));
  return mat4_identity(out);
}

void mat4_free(mat4 *a) {
  free(a);
}

mat4 *mat4_clone(const mat4 *a) {
  mat4 *out = mat4_create();
  mat4_copy(out, a);
  return out;
}

mat4 *mat4_from_values(
  float m00,
  float m01,
  float m02,
  float m03,
  float m10,
  float m11,
  float m12,
  float m13,
  float m20,
  float m21,
  float m22,
  float m23,
  float m30,
  float m31,
  float m32,
  float m33
) {
  return mat4_set(
    mat4_create(),
    m00, m01, m02, m03,
    m10, m11, m12, m13,
    m20, m21, m22, m23,
    m30, m31, m32, m33
  );
}

mat4 *mat4_copy(mat4 *out, const mat4 *a) {
  memcpy(out->data, a->data, sizeof(a->data));
  return out;
}

mat4 *mat4_identity(mat4 *out) {
  return mat4_set(
    out,
    1.f, 0.f, 0.f, 0.f,
    0.f, 1.f, 0.f, 0.f,
    0.f, 0.f, 1.f, 0.f,
    0.f, 0.f, 0.f, 1.f
  );
}

mat4 *mat4_set(
  mat4 *out,
  float m00,
  float m01,
  float m02,
  float m03,
  float m10,
  float m11,
  float m12,
  float m13,
  float m20,
  float m21,
  float m22,
  float m23,
  float m30,
  float m31,
  float m32,
  float m33
) {
  out->m00 = m00;
  out->m01 = m01;
  out->m02 = m02;
  out->m03 = m03;
  out->m10 = m10;
  out->m11 = m11;
  out->m12 = m12;
  out->m13 = m13;
  out->m20 = m20;
  out->m21 = m21;
  out->m22 = m22;
  out->m23 = m23;
  out->m30 = m30;
  out->m31 = m31;
  out->m32 = m32;
  out->m33 = m33;
  return out;
}

mat4 *mat4_transpose(mat4 *out, const mat4 *a) {
  if (out == a) {
    float a01 = a->data[1];
    float a02 = a->data[2];
    float a03 = a->data[3];
    float a12 = a->data[6];
    float a13 = a->data[7];
    float a23 = a->data[11];
    out->data[1] = a->data[4];
    out->data[2] = a->data[8];
    out->data[3] = a->data[12];
    out->data[4] = a01;
    out->data[6] = a->data[9];
    out->data[7] = a->data[13];
    out->data[8] = a02;
    out->data[9] = a12;
    out->data[11] = a->data[14];
    out->data[12] = a03;
    out->data[13] = a13;
    out->data[14] = a23;
  } else {
    out->data[0] = a->data[0];
    out->data[1] = a->data[4];
    out->data[2] = a->data[8];
    out->data[3] = a->data[12];
    out->data[4] = a->data[1];
    out->data[5] = a->data[5];
    out->data[6] = a->data[9];
    out->data[7] = a->data[13];
    out->data[8] = a->data[2];
    out->data[9] = a->data[6];
    out->data[10] = a->data[10];
    out->data[11] = a->data[14];
    out->data[12] = a->data[3];
    out->data[13] = a->data[7];
    out->data[14] = a->data[11];
    out->data[15] = a->data[15];
  }

  return out;
}

mat4 *mat4_invert(mat4 *out, const mat4 *a) {
  float a00 = a->data[0], a01 = a->data[1], a02 = a->data[2], a03 = a->data[3];
  float a10 = a->data[4], a11 = a->data[5], a12 = a->data[6], a13 = a->data[7];
  float a20 = a->data[8], a21 = a->data[9], a22 = a->data[10], a23 = a->data[11];
  float a30 = a->data[12], a31 = a->data[13], a32 = a->data[14], a33 = a->data[15];

  float b00 = a00 * a11 - a01 * a10;
  float b01 = a00 * a12 - a02 * a10;
  float b02 = a00 * a13 - a03 * a10;
  float b03 = a01 * a12 - a02 * a11;
  float b04 = a01 * a13 - a03 * a11;
  float b05 = a02 * a13 - a03 * a12;
  float b06 = a20 * a31 - a21 * a30;
  float b07 = a20 * a32 - a22 * a30;
  float b08 = a20 * a33 - a23 * a30;
  float b09 = a21 * a32 - a22 * a31;
  float b10 = a21 * a33 - a23 * a31;
  float b11 = a22 * a33 - a23 * a32;

  // Calculate the determinant
  float det = b00 * b11 - b01 * b10 + b02 * b09 + b03 * b08 - b04 * b07 + b05 * b06;

  if (det == 0.f) {
    return NULL;
  }

  det = 1.f / det;

  out->data[0] = (a11 * b11 - a12 * b10 + a13 * b09) * det;
  out->data[1] = (a02 * b10 - a01 * b11 - a03 * b09) * det;
  out->data[2] = (a31 * b05 - a32 * b04 + a33 * b03) * det;
  out->data[3] = (a22 * b04 - a21 * b05 - a23 * b03) * det;
  out->data[4] = (a12 * b08 - a10 * b11 - a13 * b07) * det;
  out->data[5] = (a00 * b11 - a02 * b08 + a03 * b07) * det;
  out->data[6] = (a32 * b02 - a30 * b05 - a33 * b01) * det;
  out->data[7] = (a20 * b05 - a22 * b02 + a23 * b01) * det;
  out->data[8] = (a10 * b10 - a11 * b08 + a13 * b06) * det;
  out->data[9] = (a01 * b08 - a00 * b10 - a03 * b06) * det;
  out->data[10] = (a30 * b04 - a31 * b02 + a33 * b00) * det;
  out->data[11] = (a21 * b02 - a20 * b04 - a23 * b00) * det;
  out->data[12] = (a11 * b07 - a10 * b09 - a12 * b06) * det;
  out->data[13] = (a00 * b09 - a01 * b07 + a02 * b06) * det;
  out->data[14] = (a31 * b01 - a30 * b03 - a32 * b00) * det;
  out->data[15] = (a20 * b03 - a21 * b01 + a22 * b00) * det;
  return out;
}

mat4 *mat4_adjoint(mat4 *out, const mat4 *a) {
  float a00 = a->data[0], a01 = a->data[1], a02 = a->data[2], a03 = a->data[3];
  float a10 = a->data[4], a11 = a->data[5], a12 = a->data[6], a13 = a->data[7];
  float a20 = a->data[8], a21 = a->data[9], a22 = a->data[10], a23 = a->data[11];
  float a30 = a->data[12], a31 = a->data[13], a32 = a->data[14], a33 = a->data[15];

  out->data[0] =  (a11 * (a22 * a33 - a23 * a32) - a21 * (a12 * a33 - a13 * a32) + a31 * (a12 * a23 - a13 * a22));
  out->data[1] = -(a01 * (a22 * a33 - a23 * a32) - a21 * (a02 * a33 - a03 * a32) + a31 * (a02 * a23 - a03 * a22));
  out->data[2] =  (a01 * (a12 * a33 - a13 * a32) - a11 * (a02 * a33 - a03 * a32) + a31 * (a02 * a13 - a03 * a12));
  out->data[3] = -(a01 * (a12 * a23 - a13 * a22) - a11 * (a02 * a23 - a03 * a22) + a21 * (a02 * a13 - a03 * a12));
  out->data[4] = -(a10 * (a22 * a33 - a23 * a32) - a20 * (a12 * a33 - a13 * a32) + a30 * (a12 * a23 - a13 * a22));
  out->data[5] =  (a00 * (a22 * a33 - a23 * a32) - a20 * (a02 * a33 - a03 * a32) + a30 * (a02 * a23 - a03 * a22));
  out->data[6] = -(a00 * (a12 * a33 - a13 * a32) - a10 * (a02 * a33 - a03 * a32) + a30 * (a02 * a13 - a03 * a12));
  out->data[7] =  (a00 * (a12 * a23 - a13 * a22) - a10 * (a02 * a23 - a03 * a22) + a20 * (a02 * a13 - a03 * a12));
  out->data[8] =  (a10 * (a21 * a33 - a23 * a31) - a20 * (a11 * a33 - a13 * a31) + a30 * (a11 * a23 - a13 * a21));
  out->data[9] = -(a00 * (a21 * a33 - a23 * a31) - a20 * (a01 * a33 - a03 * a31) + a30 * (a01 * a23 - a03 * a21));
  out->data[10] =  (a00 * (a11 * a33 - a13 * a31) - a10 * (a01 * a33 - a03 * a31) + a30 * (a01 * a13 - a03 * a11));
  out->data[11] = -(a00 * (a11 * a23 - a13 * a21) - a10 * (a01 * a23 - a03 * a21) + a20 * (a01 * a13 - a03 * a11));
  out->data[12] = -(a10 * (a21 * a32 - a22 * a31) - a20 * (a11 * a32 - a12 * a31) + a30 * (a11 * a22 - a12 * a21));
  out->data[13] =  (a00 * (a21 * a32 - a22 * a31) - a20 * (a01 * a32 - a02 * a31) + a30 * (a01 * a22 - a02 * a21));
  out->data[14] = -(a00 * (a11 * a32 - a12 * a31) - a10 * (a01 * a32 - a02 * a31) + a30 * (a01 * a12 - a02 * a11));
  out->data[15] =  (a00 * (a11 * a22 - a12 * a21) - a10 * (a01 * a22 - a02 * a21) + a20 * (a01 * a12 - a02 * a11));
  return out;
}

float mat4_determinant(const mat4 *a) {
  float a00 = a->data[0], a01 = a->data[1], a02 = a->data[2], a03 = a->data[3];
  float a10 = a->data[4], a11 = a->data[5], a12 = a->data[6], a13 = a->data[7];
  float a20 = a->data[8], a21 = a->data[9], a22 = a->data[10], a23 = a->data[11];
  float a30 = a->data[12], a31 = a->data[13], a32 = a->data[14], a33 = a->data[15];
  
  float b00 = a00 * a11 - a01 * a10;
  float b01 = a00 * a12 - a02 * a10;
  float b02 = a00 * a13 - a03 * a10;
  float b03 = a01 * a12 - a02 * a11;
  float b04 = a01 * a13 - a03 * a11;
  float b05 = a02 * a13 - a03 * a12;
  float b06 = a20 * a31 - a21 * a30;
  float b07 = a20 * a32 - a22 * a30;
  float b08 = a20 * a33 - a23 * a30;
  float b09 = a21 * a32 - a22 * a31;
  float b10 = a21 * a33 - a23 * a31;
  float b11 = a22 * a33 - a23 * a32;

  // Calculate the determinant
  return b00 * b11 - b01 * b10 + b02 * b09 + b03 * b08 - b04 * b07 + b05 * b06;
}

mat4 *mat4_multiply(mat4 *out, const mat4 *a, const mat4 *b) {
  float a00 = a->data[0], a01 = a->data[1], a02 = a->data[2], a03 = a->data[3];
  float a10 = a->data[4], a11 = a->data[5], a12 = a->data[6], a13 = a->data[7];
  float a20 = a->data[8], a21 = a->data[9], a22 = a->data[10], a23 = a->data[11];
  float a30 = a->data[12], a31 = a->data[13], a32 = a->data[14], a33 = a->data[15];
  
  // Cache only the current line of the second matrix
  float b0 = b->data[0], b1 = b->data[1], b2 = b->data[2], b3 = b->data[3];
  out->data[0] = b0*a00 + b1*a10 + b2*a20 + b3*a30;
  out->data[1] = b0*a01 + b1*a11 + b2*a21 + b3*a31;
  out->data[2] = b0*a02 + b1*a12 + b2*a22 + b3*a32;
  out->data[3] = b0*a03 + b1*a13 + b2*a23 + b3*a33;
  
  b0 = b->data[4]; b1 = b->data[5]; b2 = b->data[6]; b3 = b->data[7];
  out->data[4] = b0*a00 + b1*a10 + b2*a20 + b3*a30;
  out->data[5] = b0*a01 + b1*a11 + b2*a21 + b3*a31;
  out->data[6] = b0*a02 + b1*a12 + b2*a22 + b3*a32;
  out->data[7] = b0*a03 + b1*a13 + b2*a23 + b3*a33;
  
  b0 = b->data[8]; b1 = b->data[9]; b2 = b->data[10]; b3 = b->data[11];
  out->data[8] = b0*a00 + b1*a10 + b2*a20 + b3*a30;
  out->data[9] = b0*a01 + b1*a11 + b2*a21 + b3*a31;
  out->data[10] = b0*a02 + b1*a12 + b2*a22 + b3*a32;
  out->data[11] = b0*a03 + b1*a13 + b2*a23 + b3*a33;
  
  b0 = b->data[12]; b1 = b->data[13]; b2 = b->data[14]; b3 = b->data[15];
  out->data[12] = b0*a00 + b1*a10 + b2*a20 + b3*a30;
  out->data[13] = b0*a01 + b1*a11 + b2*a21 + b3*a31;
  out->data[14] = b0*a02 + b1*a12 + b2*a22 + b3*a32;
  out->data[15] = b0*a03 + b1*a13 + b2*a23 + b3*a33;
  
  return out;
}

mat4 *mat4_translate(mat4 *out, const mat4 *a, const vec4 *v) {
  float x = v->x, y = v->y, z = v->z;
  float a00, a01, a02, a03;
  float a10, a11, a12, a13;
  float a20, a21, a22, a23;
  
  if (a == out) {
    out->data[12] = a->data[0] * x + a->data[4] * y + a->data[8] * z + a->data[12];
    out->data[13] = a->data[1] * x + a->data[5] * y + a->data[9] * z + a->data[13];
    out->data[14] = a->data[2] * x + a->data[6] * y + a->data[10] * z + a->data[14];
    out->data[15] = a->data[3] * x + a->data[7] * y + a->data[11] * z + a->data[15];
  } else {
    a00 = a->data[0]; a01 = a->data[1]; a02 = a->data[2]; a03 = a->data[3];
    a10 = a->data[4]; a11 = a->data[5]; a12 = a->data[6]; a13 = a->data[7];
    a20 = a->data[8]; a21 = a->data[9]; a22 = a->data[10]; a23 = a->data[11];
    out->data[0] = a00; out->data[1] = a01; out->data[2] = a02; out->data[3] = a03;
    out->data[4] = a10; out->data[5] = a11; out->data[6] = a12; out->data[7] = a13;
    out->data[8] = a20; out->data[9] = a21; out->data[10] = a22; out->data[11] = a23;
    out->data[12] = a00 * x + a10 * y + a20 * z + a->data[12];
    out->data[13] = a01 * x + a11 * y + a21 * z + a->data[13];
    out->data[14] = a02 * x + a12 * y + a22 * z + a->data[14];
    out->data[15] = a03 * x + a13 * y + a23 * z + a->data[15];
  }
  return out;
}

mat4 *mat4_rotate(mat4 *out, const mat4 *a, float angle, const vec3 *axis) {
  float x = axis->x, y = axis->y, z = axis->z;
  float len = sqrtf(x * x + y * y + z * z);
  float s, c, t;
  float a00, a01, a02, a03;
  float a10, a11, a12, a13;
  float a20, a21, a22, a23;
  float b00, b01, b02;
  float b10, b11, b12;
  float b20, b21, b22;
  
  if (len < MMATH_EPSILON) return NULL;

  len = 1.f / len;
  x *= len;
  y *= len;
  z *= len;

  s = sinf(angle);
  c = cosf(angle);
  t = 1.f - c;
  
  a00 = a->data[0]; a01 = a->data[1]; a02 = a->data[2]; a03 = a->data[3];
  a10 = a->data[4]; a11 = a->data[5]; a12 = a->data[6]; a13 = a->data[7];
  a20 = a->data[8]; a21 = a->data[9]; a22 = a->data[10]; a23 = a->data[11];

  // Construct the elements of the rotation matrix
  b00 = x * x * t + c; b01 = y * x * t + z * s; b02 = z * x * t - y * s;
  b10 = x * y * t - z * s; b11 = y * y * t + c; b12 = z * y * t + x * s;
  b20 = x * z * t + y * s; b21 = y * z * t - x * s; b22 = z * z * t + c;

  // Perform rotation-specific matrix multiplication
  out->data[0] = a00 * b00 + a10 * b01 + a20 * b02;
  out->data[1] = a01 * b00 + a11 * b01 + a21 * b02;
  out->data[2] = a02 * b00 + a12 * b01 + a22 * b02;
  out->data[3] = a03 * b00 + a13 * b01 + a23 * b02;
  out->data[4] = a00 * b10 + a10 * b11 + a20 * b12;
  out->data[5] = a01 * b10 + a11 * b11 + a21 * b12;
  out->data[6] = a02 * b10 + a12 * b11 + a22 * b12;
  out->data[7] = a03 * b10 + a13 * b11 + a23 * b12;
  out->data[8] = a00 * b20 + a10 * b21 + a20 * b22;
  out->data[9] = a01 * b20 + a11 * b21 + a21 * b22;
  out->data[10] = a02 * b20 + a12 * b21 + a22 * b22;
  out->data[11] = a03 * b20 + a13 * b21 + a23 * b22;
  
  if (a != out) {
    out->data[12] = a->data[12];
    out->data[13] = a->data[13];
    out->data[14] = a->data[14];
    out->data[15] = a->data[15];
  }

  return out;
}

mat4 *mat4_rotate_x(mat4 *out, const mat4 *a, float angle) {
  float s = sinf(angle);
  float c = cosf(angle);
  float a10 = a->data[4];
  float a11 = a->data[5];
  float a12 = a->data[6];
  float a13 = a->data[7];
  float a20 = a->data[8];
  float a21 = a->data[9];
  float a22 = a->data[10];
  float a23 = a->data[11];

  if (a != out) {
    out->data[0] = a->data[0];
    out->data[1] = a->data[1];
    out->data[2] = a->data[2];
    out->data[3] = a->data[3];
    out->data[12] = a->data[12];
    out->data[13] = a->data[13];
    out->data[14] = a->data[14];
    out->data[15] = a->data[15];
  }

  out->data[4] = a10 * c + a20 * s;
  out->data[5] = a11 * c + a21 * s;
  out->data[6] = a12 * c + a22 * s;
  out->data[7] = a13 * c + a23 * s;
  out->data[8] = a20 * c - a10 * s;
  out->data[9] = a21 * c - a11 * s;
  out->data[10] = a22 * c - a12 * s;
  out->data[11] = a23 * c - a13 * s;

  return out;
}

mat4 *mat4_rotate_y(mat4 *out, const mat4 *a, float angle) {
  float s = sinf(angle);
  float c = cosf(angle);
  float a00 = a->data[0];
  float a01 = a->data[1];
  float a02 = a->data[2];
  float a03 = a->data[3];
  float a20 = a->data[8];
  float a21 = a->data[9];
  float a22 = a->data[10];
  float a23 = a->data[11];

  if (a != out) {
    out->data[4] = a->data[4];
    out->data[5] = a->data[5];
    out->data[6] = a->data[6];
    out->data[7] = a->data[7];
    out->data[12] = a->data[12];
    out->data[13] = a->data[13];
    out->data[14] = a->data[14];
    out->data[15] = a->data[15];
  }

  out->data[0] = a00 * c - a20 * s;
  out->data[1] = a01 * c - a21 * s;
  out->data[2] = a02 * c - a22 * s;
  out->data[3] = a03 * c - a23 * s;
  out->data[8] = a00 * s + a20 * c;
  out->data[9] = a01 * s + a21 * c;
  out->data[10] = a02 * s + a22 * c;
  out->data[11] = a03 * s + a23 * c;

  return out;
}

mat4 *mat4_rotate_z(mat4 *out, const mat4 *a, float angle) {
  float s = sinf(angle);
  float c = cosf(angle);
  float a00 = a->data[0];
  float a01 = a->data[1];
  float a02 = a->data[2];
  float a03 = a->data[3];
  float a10 = a->data[4];
  float a11 = a->data[5];
  float a12 = a->data[6];
  float a13 = a->data[7];

  if (a != out) {
    out->data[8] = a->data[8];
    out->data[9] = a->data[9];
    out->data[10] = a->data[10];
    out->data[11] = a->data[11];
    out->data[12] = a->data[12];
    out->data[13] = a->data[13];
    out->data[14] = a->data[14];
    out->data[15] = a->data[15];
  }

  out->data[0] = a00 * c + a10 * s;
  out->data[1] = a01 * c + a11 * s;
  out->data[2] = a02 * c + a12 * s;
  out->data[3] = a03 * c + a13 * s;
  out->data[4] = a10 * c - a00 * s;
  out->data[5] = a11 * c - a01 * s;
  out->data[6] = a12 * c - a02 * s;
  out->data[7] = a13 * c - a03 * s;

  return out;
}

mat4 *mat4_scale(mat4 *out, const mat4 *a, const vec4 *v) {
  float x = v->x, y = v->y, z = v->z;

  out->data[0] = a->data[0] * x;
  out->data[1] = a->data[1] * x;
  out->data[2] = a->data[2] * x;
  out->data[3] = a->data[3] * x;
  out->data[4] = a->data[4] * y;
  out->data[5] = a->data[5] * y;
  out->data[6] = a->data[6] * y;
  out->data[7] = a->data[7] * y;
  out->data[8] = a->data[8] * z;
  out->data[9] = a->data[9] * z;
  out->data[10] = a->data[10] * z;
  out->data[11] = a->data[11] * z;
  out->data[12] = a->data[12];
  out->data[13] = a->data[13];
  out->data[14] = a->data[14];
  out->data[15] = a->data[15];
  return out;
}

mat4 *mat4_from_translation(mat4 *out, const vec4 *v) {
  out->data[0] = 1;
  out->data[1] = 0;
  out->data[2] = 0;
  out->data[3] = 0;
  out->data[4] = 0;
  out->data[5] = 1;
  out->data[6] = 0;
  out->data[7] = 0;
  out->data[8] = 0;
  out->data[9] = 0;
  out->data[10] = 1;
  out->data[11] = 0;
  out->data[12] = v->x;
  out->data[13] = v->y;
  out->data[14] = v->z;
  out->data[15] = 1;
  return out;
}

mat4 *mat4_from_rotation(mat4 *out, float angle, const vec3 *axis) {
  float x = axis->x, y = axis->y, z = axis->z;
  float len = sqrtf(x * x + y * y + z * z);
  float s, c, t;

  if (len < MMATH_EPSILON) return NULL;

  len = 1.f / len;
  x *= len;
  y *= len;
  z *= len;

  s = sinf(angle);
  c = cosf(angle);
  t = 1.f - c;
  
  out->data[0] = x * x * t + c;
  out->data[1] = y * x * t + z * s;
  out->data[2] = z * x * t - y * s;
  out->data[3] = 0;
  out->data[4] = x * y * t - z * s;
  out->data[5] = y * y * t + c;
  out->data[6] = z * y * t + x * s;
  out->data[7] = 0;
  out->data[8] = x * z * t + y * s;
  out->data[9] = y * z * t - x * s;
  out->data[10] = z * z * t + c;
  out->data[11] = 0;
  out->data[12] = 0;
  out->data[13] = 0;
  out->data[14] = 0;
  out->data[15] = 1;
  return out;
}

mat4 *mat4_from_rotation_x(mat4 *out, float angle) {
  float s = sinf(angle);
  float c = cosf(angle);

  out->data[0] = 1;
  out->data[1] = 0;
  out->data[2] = 0;
  out->data[3] = 0;
  out->data[4] = 0;
  out->data[5] = c;
  out->data[6] = s;
  out->data[7] = 0;
  out->data[8] = 0;
  out->data[9] = -s;
  out->data[10] = c;
  out->data[11] = 0;
  out->data[12] = 0;
  out->data[13] = 0;
  out->data[14] = 0;
  out->data[15] = 1;
  return out;
}

mat4 *mat4_from_rotation_y(mat4 *out, float angle) {
  float s = sinf(angle);
  float c = cosf(angle);

  out->data[0] = c;
  out->data[1] = 0;
  out->data[2] = -s;
  out->data[3] = 0;
  out->data[4] = 0;
  out->data[5] = 1;
  out->data[6] = 0;
  out->data[7] = 0;
  out->data[8] = s;
  out->data[9] = 0;
  out->data[10] = c;
  out->data[11] = 0;
  out->data[12] = 0;
  out->data[13] = 0;
  out->data[14] = 0;
  out->data[15] = 1;
  return out;
}

mat4 *mat4_from_rotation_z(mat4 *out, float angle) {
  float s = sinf(angle);
  float c = cosf(angle);

  out->data[0] = c;
  out->data[1] = s;
  out->data[2] = 0;
  out->data[3] = 0;
  out->data[4] = -s;
  out->data[5] = c;
  out->data[6] = 0;
  out->data[7] = 0;
  out->data[8] = 0;
  out->data[9] = 0;
  out->data[10] = 1;
  out->data[11] = 0;
  out->data[12] = 0;
  out->data[13] = 0;
  out->data[14] = 0;
  out->data[15] = 1;
  return out;
}

mat4 *mat4_from_scaling(mat4 *out, const vec4 *v) {
  out->data[0] = v->x;
  out->data[1] = 0;
  out->data[2] = 0;
  out->data[3] = 0;
  out->data[4] = 0;
  out->data[5] = v->y;
  out->data[6] = 0;
  out->data[7] = 0;
  out->data[8] = 0;
  out->data[9] = 0;
  out->data[10] = v->z;
  out->data[11] = 0;
  out->data[12] = 0;
  out->data[13] = 0;
  out->data[14] = 0;
  out->data[15] = 1;
  return out;
}

mat4 *mat4_from_rotation_translation(mat4 *out, const quat *q, const vec3 *v) {
  float x = q->x, y = q->y, z = q->z, w = q->w;
  float x2 = x + x;
  float y2 = y + y;
  float z2 = z + z;

  float xx = x * x2;
  float xy = x * y2;
  float xz = x * z2;
  float yy = y * y2;
  float yz = y * z2;
  float zz = z * z2;
  float wx = w * x2;
  float wy = w * y2;
  float wz = w * z2;

  out->data[0] = 1 - (yy + zz);
  out->data[1] = xy + wz;
  out->data[2] = xz - wy;
  out->data[3] = 0;
  out->data[4] = xy - wz;
  out->data[5] = 1 - (xx + zz);
  out->data[6] = yz + wx;
  out->data[7] = 0;
  out->data[8] = xz + wy;
  out->data[9] = yz - wx;
  out->data[10] = 1 - (xx + yy);
  out->data[11] = 0;
  out->data[12] = v->x;
  out->data[13] = v->y;
  out->data[14] = v->z;
  out->data[15] = 1;
  return out;
}

mat4 *mat4_from_quat2(mat4 *out, const quat2 *a) {
  vec3 translation;

  float bx = -a->x1, by = -a->y1, bz = -a->z1, bw = a->w1;
  float ax = a->x2, ay = a->y2, az = a->z2, aw = a->w2;

  float magnitude = bx * bx + by * by + bz * bz + bw * bw;

  if (magnitude > 0.f) {
    translation.x = (ax * bw + aw * bx + ay * bz - az * by) * 2 / magnitude;
    translation.y = (ay * bw + aw * by + az * bx - ax * bz) * 2 / magnitude;
    translation.z = (az * bw + aw * bz + ax * by - ay * bx) * 2 / magnitude;
  } else {
    translation.x = (ax * bw + aw * bx + ay * bz - az * by) * 2;
    translation.y = (ay * bw + aw * by + az * bx - ax * bz) * 2;
    translation.z = (az * bw + aw * bz + ax * by - ay * bx) * 2;
  }

  return mat4_from_rotation_translation(out, a, &translation);
}

vec3 *mat4_get_translation(vec3 *out, const mat4 *m) {
  out->x = m->data[12];
  out->y = m->data[13];
  out->z = m->data[14];
  return out;
}

quat *mat4_get_rotation(quat *out, const mat4 *m) {
  // Algorithm taken from http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/index.htm
  float trace = m->data[0] + m->data[5] + m->data[10];
  float S = 0.f;

  if (trace > 0.f) {
    S = sqrtf(trace + 1.f) * 2.f;
    out->data[3] = 0.25f * S;
    out->data[0] = (m->data[6] - m->data[9]) / S;
    out->data[1] = (m->data[8] - m->data[2]) / S;
    out->data[2] = (m->data[1] - m->data[4]) / S;
  } else if ((m->data[0] > m->data[5]) && (m->data[0] > m->data[10])) {
    S = sqrtf(1.0 + m->data[0] - m->data[5] - m->data[10]) * 2.f;
    out->data[3] = (m->data[6] - m->data[9]) / S;
    out->data[0] = 0.25f * S;
    out->data[1] = (m->data[1] + m->data[4]) / S;
    out->data[2] = (m->data[8] + m->data[2]) / S;
  } else if (m->data[5] > m->data[10]) {
    S = sqrtf(1.0 + m->data[5] - m->data[0] - m->data[10]) * 2.f;
    out->data[3] = (m->data[8] - m->data[2]) / S;
    out->data[0] = (m->data[1] + m->data[4]) / S;
    out->data[1] = 0.25f * S;
    out->data[2] = (m->data[6] + m->data[9]) / S;
  } else {
    S = sqrtf(1.0 + m->data[10] - m->data[0] - m->data[5]) * 2.f;
    out->data[3] = (m->data[1] - m->data[4]) / S;
    out->data[0] = (m->data[8] + m->data[2]) / S;
    out->data[1] = (m->data[6] + m->data[9]) / S;
    out->data[2] = 0.25f * S;
  }

  return out;
}

vec3 *mat4_get_scaling(vec3 *out, const mat4 *m) {
  float m11 = m->data[0];
  float m12 = m->data[1];
  float m13 = m->data[2];
  float m21 = m->data[4];
  float m22 = m->data[5];
  float m23 = m->data[6];
  float m31 = m->data[8];
  float m32 = m->data[9];
  float m33 = m->data[10];

  out->data[0] = sqrtf(m11 * m11 + m12 * m12 + m13 * m13);
  out->data[1] = sqrtf(m21 * m21 + m22 * m22 + m23 * m23);
  out->data[2] = sqrtf(m31 * m31 + m32 * m32 + m33 * m33);
  return out;
}

mat4 *mat4_from_rotation_translation_scale(
  mat4 *out,
  const quat *q,
  const vec3 *v,
  const vec3 *s
) {
  // Quaternion math
  float x = q->x, y = q->y, z = q->z, w = q->w;
  float x2 = x + x;
  float y2 = y + y;
  float z2 = z + z;

  float xx = x * x2;
  float xy = x * y2;
  float xz = x * z2;
  float yy = y * y2;
  float yz = y * z2;
  float zz = z * z2;
  float wx = w * x2;
  float wy = w * y2;
  float wz = w * z2;
  float sx = s->x;
  float sy = s->y;
  float sz = s->z;

  out->data[0] = (1.f - (yy + zz)) * sx;
  out->data[1] = (xy + wz) * sx;
  out->data[2] = (xz - wy) * sx;
  out->data[3] = 0.f;
  out->data[4] = (xy - wz) * sy;
  out->data[5] = (1 - (xx + zz)) * sy;
  out->data[6] = (yz + wx) * sy;
  out->data[7] = 0.f;
  out->data[8] = (xz + wy) * sz;
  out->data[9] = (yz - wx) * sz;
  out->data[10] = (1 - (xx + yy)) * sz;
  out->data[11] = 0.f;
  out->data[12] = v->x;
  out->data[13] = v->y;
  out->data[14] = v->z;
  out->data[15] = 1.f;
  return out;
}

mat4 *mat4_from_rotation_translation_scale_origin(
  mat4 *out,
  const quat *q,
  const vec3 *v,
  const vec3 *s,
  const vec3 *o
) {
  // Quaternion math
  float x = q->x, y = q->y, z = q->z, w = q->w;
  float x2 = x + x;
  float y2 = y + y;
  float z2 = z + z;

  float xx = x * x2;
  float xy = x * y2;
  float xz = x * z2;
  float yy = y * y2;
  float yz = y * z2;
  float zz = z * z2;
  float wx = w * x2;
  float wy = w * y2;
  float wz = w * z2;

  float sx = s->x;
  float sy = s->y;
  float sz = s->z;

  float ox = o->x;
  float oy = o->y;
  float oz = o->z;

  float out0 = (1.f - (yy + zz)) * sx;
  float out1 = (xy + wz) * sx;
  float out2 = (xz - wy) * sx;
  float out4 = (xy - wz) * sy;
  float out5 = (1.f - (xx + zz)) * sy;
  float out6 = (yz + wx) * sy;
  float out8 = (xz + wy) * sz;
  float out9 = (yz - wx) * sz;
  float out10 = (1.f - (xx + yy)) * sz;

  out->data[0] = out0;
  out->data[1] = out1;
  out->data[2] = out2;
  out->data[3] = 0.f;
  out->data[4] = out4;
  out->data[5] = out5;
  out->data[6] = out6;
  out->data[7] = 0.f;
  out->data[8] = out8;
  out->data[9] = out9;
  out->data[10] = out10;
  out->data[11] = 0.f;
  out->data[12] = v->x + ox - (out0 * ox + out4 * oy + out8 * oz);
  out->data[13] = v->y + oy - (out1 * ox + out5 * oy + out9 * oz);
  out->data[14] = v->z + oz - (out2 * ox + out6 * oy + out10 * oz);
  out->data[15] = 1.f;
  return out;
}

mat4 *mat4_from_quat(
  mat4 *out,
  const quat *q
) {
  float x = q->x, y = q->y, z = q->z, w = q->w;
  float x2 = x + x;
  float y2 = y + y;
  float z2 = z + z;

  float xx = x * x2;
  float yx = y * x2;
  float yy = y * y2;
  float zx = z * x2;
  float zy = z * y2;
  float zz = z * z2;
  float wx = w * x2;
  float wy = w * y2;
  float wz = w * z2;

  out->data[0] = 1.f - yy - zz;
  out->data[1] = yx + wz;
  out->data[2] = zx - wy;
  out->data[3] = 0.f;
  out->data[4] = yx - wz;
  out->data[5] = 1.f - xx - zz;
  out->data[6] = zy + wx;
  out->data[7] = 0.f;
  out->data[8] = zx + wy;
  out->data[9] = zy - wx;
  out->data[10] = 1.f - xx - yy;
  out->data[11] = 0.f;
  out->data[12] = 0.f;
  out->data[13] = 0.f;
  out->data[14] = 0.f;
  out->data[15] = 1.f;
  return out;
}

mat4 *mat4_frustum(
  mat4 *out,
  float left,
  float right,
  float bottom,
  float top,
  float near,
  float far
) {
  float rl = 1.f / (right - left);
  float tb = 1.f / (top - bottom);
  float nf = 1.f / (near - far);

  out->data[0] = (near * 2.f) * rl;
  out->data[1] = 0.f;
  out->data[2] = 0.f;
  out->data[3] = 0.f;
  out->data[4] = 0.f;
  out->data[5] = (near * 2.f) * tb;
  out->data[6] = 0.f;
  out->data[7] = 0.f;
  out->data[8] = (right + left) * rl;
  out->data[9] = (top + bottom) * tb;
  out->data[10] = (far + near) * nf;
  out->data[11] = -1.f;
  out->data[12] = 0.f;
  out->data[13] = 0.f;
  out->data[14] = (far * near * 2.f) * nf;
  out->data[15] = 0.f;
  return out;
}

mat4 *mat4_perspective(
  mat4 *out,
  float fovy,
  float aspect,
  float near,
  float far
) {
  float f = 1.f / tanf(fovy / 2.f), nf;

  out->data[0] = f / aspect;
  out->data[1] = 0.f;
  out->data[2] = 0.f;
  out->data[3] = 0.f;
  out->data[4] = 0.f;
  out->data[5] = f;
  out->data[6] = 0.f;
  out->data[7] = 0.f;
  out->data[8] = 0.f;
  out->data[9] = 0.f;
  out->data[11] = -1.f;
  out->data[12] = 0.f;
  out->data[13] = 0.f;
  out->data[15] = 0.f;

  if (far != INFINITY) {
    nf = 1.f / (near - far);
    out->data[10] = (far + near) * nf;
    out->data[14] = (2.f * far * near) * nf;
  } else {
    out->data[10] = -1.f;
    out->data[14] = -2.f * near;
  }
  return out;
}

mat4 *mat4_perspective_from_field_of_view(
  mat4 *out,
  float fovUp,
  float fovDown,
  float fovLeft,
  float fovRight,
  float near,
  float far
) {
  float upTan = tanf(fovUp * (float) M_PI / 180.f);
  float downTan = tanf(fovDown * (float) M_PI / 180.f);
  float leftTan = tanf(fovLeft * (float) M_PI / 180.f);
  float rightTan = tanf(fovRight * (float) M_PI / 180.f);
  float xScale = 2.f / (leftTan + rightTan);
  float yScale = 2.f / (upTan + downTan);
  
  out->data[0] = xScale;
  out->data[1] = 0.f;
  out->data[2] = 0.f;
  out->data[3] = 0.f;
  out->data[4] = 0.f;
  out->data[5] = yScale;
  out->data[6] = 0.f;
  out->data[7] = 0.f;
  out->data[8] = -((leftTan - rightTan) * xScale * .5f);
  out->data[9] = ((upTan - downTan) * yScale * .5f);
  out->data[10] = far / (near - far);
  out->data[11] = -1.f;
  out->data[12] = 0.f;
  out->data[13] = 0.f;
  out->data[14] = (far * near) / (near - far);
  out->data[15] = 0.f;
  return out;
}

mat4 *mat4_ortho(
  mat4 *out,
  float left,
  float right,
  float bottom,
  float top,
  float near,
  float far
) {
  float lr = 1.f / (left - right);
  float bt = 1.f / (bottom - top);
  float nf = 1.f / (near - far);

  out->data[0] = -2.f * lr;
  out->data[1] = 0.f;
  out->data[2] = 0.f;
  out->data[3] = 0.f;
  out->data[4] = 0.f;
  out->data[5] = -2.f * bt;
  out->data[6] = 0.f;
  out->data[7] = 0.f;
  out->data[8] = 0.f;
  out->data[9] = 0.f;
  out->data[10] = 2.f * nf;
  out->data[11] = 0.f;
  out->data[12] = (left + right) * lr;
  out->data[13] = (top + bottom) * bt;
  out->data[14] = (far + near) * nf;
  out->data[15] = 1.f;
  return out;
}

mat4 *mat4_look_at(
  mat4 *out,
  const vec3 *eye,
  const vec3 *center,
  const vec3 *up
) {
  float x0, x1, x2, y0, y1, y2, z0, z1, z2, len;
  float eyex = eye->x;
  float eyey = eye->y;
  float eyez = eye->z;
  float upx = up->x;
  float upy = up->y;
  float upz = up->z;
  float centerx = center->x;
  float centery = center->y;
  float centerz = center->z;

  if (
    fabsf(eyex - centerx) < MMATH_EPSILON &&
    fabsf(eyey - centery) < MMATH_EPSILON &&
    fabsf(eyez - centerz) < MMATH_EPSILON
  ) {
    return mat4_identity(out);
  }

  z0 = eyex - centerx;
  z1 = eyey - centery;
  z2 = eyez - centerz;
  
  len = 1.f / sqrtf(z0 * z0 + z1 * z1 + z2 * z2);
  z0 *= len;
  z1 *= len;
  z2 *= len;
  
  x0 = upy * z2 - upz * z1;
  x1 = upz * z0 - upx * z2;
  x2 = upx * z1 - upy * z0;
  len = sqrtf(x0 * x0 + x1 * x1 + x2 * x2);

  if (len == 0.f) {
    x0 = x1 = x2 = 0.f;
  } else {
    len = 1.f / len;
    x0 *= len;
    x1 *= len;
    x2 *= len;
  }

  y0 = z1 * x2 - z2 * x1;
  y1 = z2 * x0 - z0 * x2;
  y2 = z0 * x1 - z1 * x0;
  len = sqrtf(y0 * y0 + y1 * y1 + y2 * y2);

  if (len == 0.f) {
    y0 = y1 = y2 = 0.f;
  } else {
    len = 1.f / len;
    y0 *= len;
    y1 *= len;
    y2 *= len;
  }

  out->data[0] = x0;
  out->data[1] = y0;
  out->data[2] = z0;
  out->data[3] = 0.f;
  out->data[4] = x1;
  out->data[5] = y1;
  out->data[6] = z1;
  out->data[7] = 0.f;
  out->data[8] = x2;
  out->data[9] = y2;
  out->data[10] = z2;
  out->data[11] = 0.f;
  out->data[12] = -(x0 * eyex + x1 * eyey + x2 * eyez);
  out->data[13] = -(y0 * eyex + y1 * eyey + y2 * eyez);
  out->data[14] = -(z0 * eyex + z1 * eyey + z2 * eyez);
  out->data[15] = 1.f;
  return out;
}

mat4 *mat4_target_to(
  mat4 *out,
  const vec3 *eye,
  const vec3 *target,
  const vec3 *up
) {
  float len;
  float eyex = eye->x;
  float eyey = eye->y;
  float eyez = eye->z;
  float upx = up->x;
  float upy = up->y;
  float upz = up->z;
  float z0 = eyex - target->x;
  float z1 = eyey - target->y;
  float z2 = eyez - target->z;

  len = z0 * z0 + z1 * z1 + z2 * z2;
  if (len > 0.f) {
    len = 1.f / sqrtf(len);
    z0 *= len;
    z1 *= len;
    z2 *= len;
  }

  float x0 = upy * z2 - upz * z1;
  float x1 = upz * z0 - upx * z2;
  float x2 = upx * z1 - upy * z0;
  
  len = x0 * x0 + x1 * x1 + x2 * x2;
  if (len > 0.f) {
    len = 1.f / sqrtf(len);
    x0 *= len;
    x1 *= len;
    x2 *= len;
  }

  out->data[0] = x0;
  out->data[1] = x1;
  out->data[2] = x2;
  out->data[3] = 0.f;
  out->data[4] = z1 * x2 - z2 * x1;
  out->data[5] = z2 * x0 - z0 * x2;
  out->data[6] = z0 * x1 - z1 * x0;
  out->data[7] = 0.f;
  out->data[8] = z0;
  out->data[9] = z1;
  out->data[10] = z2;
  out->data[11] = 0.f;
  out->data[12] = eyex;
  out->data[13] = eyey;
  out->data[14] = eyez;
  out->data[15] = 1.f;
  return out;
}

float mat4_frob(const mat4 *a) {
  float a0 = a->data[0];
  float a1 = a->data[1];
  float a2 = a->data[2];
  float a3 = a->data[3];
  float a4 = a->data[4];
  float a5 = a->data[5];
  float a6 = a->data[6];
  float a7 = a->data[7];
  float a8 = a->data[8];
  float a9 = a->data[9];
  float a10 = a->data[10];
  float a11 = a->data[11];
  float a12 = a->data[12];
  float a13 = a->data[13];
  float a14 = a->data[14];
  float a15 = a->data[15];

  return sqrtf(
    a0 * a0 +
    a1 * a1 +
    a2 * a2 +
    a3 * a3 +
    a4 * a4 +
    a5 * a5 +
    a6 * a6 +
    a7 * a7 +
    a8 * a8 +
    a9 * a9 +
    a10 * a10 +
    a11 * a11 +
    a12 * a12 +
    a13 * a13 +
    a14 * a14 +
    a15 * a15
  );
}

mat4 *mat4_add(mat4 *out, const mat4 *a, const mat4 *b) {
  out->data[0] = a->data[0] + b->data[0];
  out->data[1] = a->data[1] + b->data[1];
  out->data[2] = a->data[2] + b->data[2];
  out->data[3] = a->data[3] + b->data[3];
  out->data[4] = a->data[4] + b->data[4];
  out->data[5] = a->data[5] + b->data[5];
  out->data[6] = a->data[6] + b->data[6];
  out->data[7] = a->data[7] + b->data[7];
  out->data[8] = a->data[8] + b->data[8];
  out->data[9] = a->data[9] + b->data[9];
  out->data[10] = a->data[10] + b->data[10];
  out->data[11] = a->data[11] + b->data[11];
  out->data[12] = a->data[12] + b->data[12];
  out->data[13] = a->data[13] + b->data[13];
  out->data[14] = a->data[14] + b->data[14];
  out->data[15] = a->data[15] + b->data[15];

  return out;
}

mat4 *mat4_subtract(mat4 *out, const mat4 *a, const mat4 *b) {
  out->data[0] = a->data[0] - b->data[0];
  out->data[1] = a->data[1] - b->data[1];
  out->data[2] = a->data[2] - b->data[2];
  out->data[3] = a->data[3] - b->data[3];
  out->data[4] = a->data[4] - b->data[4];
  out->data[5] = a->data[5] - b->data[5];
  out->data[6] = a->data[6] - b->data[6];
  out->data[7] = a->data[7] - b->data[7];
  out->data[8] = a->data[8] - b->data[8];
  out->data[9] = a->data[9] - b->data[9];
  out->data[10] = a->data[10] - b->data[10];
  out->data[11] = a->data[11] - b->data[11];
  out->data[12] = a->data[12] - b->data[12];
  out->data[13] = a->data[13] - b->data[13];
  out->data[14] = a->data[14] - b->data[14];
  out->data[15] = a->data[15] - b->data[15];

  return out;
}

mat4 *mat4_multiply_scalar(mat4 *out, const mat4 *a, float scale) {
  out->data[0] = a->data[0] * scale;
  out->data[1] = a->data[1] * scale;
  out->data[2] = a->data[2] * scale;
  out->data[3] = a->data[3] * scale;
  out->data[4] = a->data[4] * scale;
  out->data[5] = a->data[5] * scale;
  out->data[6] = a->data[6] * scale;
  out->data[7] = a->data[7] * scale;
  out->data[8] = a->data[8] * scale;
  out->data[9] = a->data[9] * scale;
  out->data[10] = a->data[10] * scale;
  out->data[11] = a->data[11] * scale;
  out->data[12] = a->data[12] * scale;
  out->data[13] = a->data[13] * scale;
  out->data[14] = a->data[14] * scale;
  out->data[15] = a->data[15] * scale;

  return out;
}

mat4 *mat4_multiply_scalar_and_add(mat4 *out, const mat4 *a, const mat4 *b, float scale) {
  out->data[0] = a->data[0] + (b->data[0] * scale);
  out->data[1] = a->data[1] + (b->data[1] * scale);
  out->data[2] = a->data[2] + (b->data[2] * scale);
  out->data[3] = a->data[3] + (b->data[3] * scale);
  out->data[4] = a->data[4] + (b->data[4] * scale);
  out->data[5] = a->data[5] + (b->data[5] * scale);
  out->data[6] = a->data[6] + (b->data[6] * scale);
  out->data[7] = a->data[7] + (b->data[7] * scale);
  out->data[8] = a->data[8] + (b->data[8] * scale);
  out->data[9] = a->data[9] + (b->data[9] * scale);
  out->data[10] = a->data[10] + (b->data[10] * scale);
  out->data[11] = a->data[11] + (b->data[11] * scale);
  out->data[12] = a->data[12] + (b->data[12] * scale);
  out->data[13] = a->data[13] + (b->data[13] * scale);
  out->data[14] = a->data[14] + (b->data[14] * scale);
  out->data[15] = a->data[15] + (b->data[15] * scale);

  return out;
}

bool mat4_exact_equals(const mat4 *a, const mat4 *b) {
  return (
    a->data[0] == b->data[0] &&
    a->data[1] == b->data[1] &&
    a->data[2] == b->data[2] &&
    a->data[3] == b->data[3] &&
    a->data[4] == b->data[4] &&
    a->data[5] == b->data[5] &&
    a->data[6] == b->data[6] &&
    a->data[7] == b->data[7] &&
    a->data[8] == b->data[8] &&
    a->data[9] == b->data[9] &&
    a->data[10] == b->data[10] &&
    a->data[11] == b->data[11] &&
    a->data[12] == b->data[12] &&
    a->data[13] == b->data[13] &&
    a->data[14] == b->data[14] &&
    a->data[15] == b->data[15]
  );
}

bool mat4_equals(const mat4 *a, const mat4 *b) {
  float a0 = a->data[0];
  float a1 = a->data[1];
  float a2 = a->data[2];
  float a3 = a->data[3];
  float a4 = a->data[4];
  float a5 = a->data[5];
  float a6 = a->data[6];
  float a7 = a->data[7];
  float a8 = a->data[8];
  float a9 = a->data[9];
  float a10 = a->data[10];
  float a11 = a->data[11];
  float a12 = a->data[12];
  float a13 = a->data[13];
  float a14 = a->data[14];
  float a15 = a->data[15];
  float b0 = b->data[0];
  float b1 = b->data[1];
  float b2 = b->data[2];
  float b3 = b->data[3];
  float b4 = b->data[4];
  float b5 = b->data[5];
  float b6 = b->data[6];
  float b7 = b->data[7];
  float b8 = b->data[8];
  float b9 = b->data[9];
  float b10 = b->data[10];
  float b11 = b->data[11];
  float b12 = b->data[12];
  float b13 = b->data[13];
  float b14 = b->data[14];
  float b15 = b->data[15];

  return (
    fabsf(a0 - b0) <= MMATH_EPSILON * fmaxf(1.f, fmaxf(fabsf(a0), fabsf(b0))) &&
    fabsf(a1 - b1) <= MMATH_EPSILON * fmaxf(1.f, fmaxf(fabsf(a1), fabsf(b1))) &&
    fabsf(a2 - b2) <= MMATH_EPSILON * fmaxf(1.f, fmaxf(fabsf(a2), fabsf(b2))) &&
    fabsf(a3 - b3) <= MMATH_EPSILON * fmaxf(1.f, fmaxf(fabsf(a3), fabsf(b3))) &&
    fabsf(a4 - b4) <= MMATH_EPSILON * fmaxf(1.f, fmaxf(fabsf(a4), fabsf(b4))) &&
    fabsf(a5 - b5) <= MMATH_EPSILON * fmaxf(1.f, fmaxf(fabsf(a5), fabsf(b5))) &&
    fabsf(a6 - b6) <= MMATH_EPSILON * fmaxf(1.f, fmaxf(fabsf(a6), fabsf(b6))) &&
    fabsf(a7 - b7) <= MMATH_EPSILON * fmaxf(1.f, fmaxf(fabsf(a7), fabsf(b7))) &&
    fabsf(a8 - b8) <= MMATH_EPSILON * fmaxf(1.f, fmaxf(fabsf(a8), fabsf(b8))) &&
    fabsf(a9 - b9) <= MMATH_EPSILON * fmaxf(1.f, fmaxf(fabsf(a9), fabsf(b9))) &&
    fabsf(a10 - b10) <= MMATH_EPSILON * fmaxf(1.f, fmaxf(fabsf(a10), fabsf(b10))) &&
    fabsf(a11 - b11) <= MMATH_EPSILON * fmaxf(1.f, fmaxf(fabsf(a11), fabsf(b11))) &&
    fabsf(a12 - b12) <= MMATH_EPSILON * fmaxf(1.f, fmaxf(fabsf(a12), fabsf(b12))) &&
    fabsf(a13 - b13) <= MMATH_EPSILON * fmaxf(1.f, fmaxf(fabsf(a13), fabsf(b13))) &&
    fabsf(a14 - b14) <= MMATH_EPSILON * fmaxf(1.f, fmaxf(fabsf(a14), fabsf(b14))) &&
    fabsf(a15 - b15) <= MMATH_EPSILON * fmaxf(1.f, fmaxf(fabsf(a15), fabsf(b15)))
  );
}
