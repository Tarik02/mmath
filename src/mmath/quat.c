#include "mmath/quat.h"
#include "mmath_private.h"

quat *quat_create() {
  quat *out = malloc(sizeof(quat));
  return quat_identity(out);
}

void quat_free(quat *a) {
  free(a);
}

quat *quat_clone(const quat *a) {
  quat *out = quat_create();
  quat_copy(out, a);
  return out;
}

quat *quat_from_values(float x, float y, float z, float w) {
  return quat_set(quat_create(), x, y, z, w);
}

quat *quat_copy(quat *out, const quat *a) {
  memcpy(out->data, a->data, sizeof(a->data));
  return out;
}

quat *quat_identity(quat *out) {
  return quat_set(out, 0.f, 0.f, 0.f, 1.f);
}

quat *quat_set(quat *out, float x, float y, float z, float w) {
  out->x = x;
  out->y = y;
  out->z = z;
  out->w = w;
  return out;
}

float quat_get_axis_angle(quat *out_axis, const quat *q) {
  float angle = acosf(q->w);
  float s = sinf(angle);

  if (s > MMATH_EPSILON) {
    out_axis->x = q->x / s;
    out_axis->y = q->y / s;
    out_axis->z = q->z / s;
  } else {
    out_axis->x = 1;
    out_axis->y = 0;
    out_axis->z = 0;
  }

  return angle * 2.f;
}

quat *quat_set_axis_angle(quat *out, const vec3 *axis, float angle) {
  angle *= .5f;
  float s = sinf(angle);

  out->x = s * axis->x;
  out->y = s * axis->y;
  out->z = s * axis->z;
  out->w = cosf(angle);
  return out;
}

quat *quat_multiply(quat *out, const quat *a, const quat *b) {
  float ax = a->x;
  float ay = a->y;
  float az = a->z;
  float aw = a->w;
  float bx = b->x;
  float by = b->y;
  float bz = b->z;
  float bw = b->w;

  out->x = ax * bw + aw * bx + ay * bz - az * by;
  out->y = ay * bw + aw * by + az * bx - ax * bz;
  out->z = az * bw + aw * bz + ax * by - ay * bx;
  out->w = aw * bw - ax * bx - ay * by - az * bz;
  return out;
}

quat *quat_rotate_x(quat *out, const quat *a, float angle) {
  angle *= .5f;

  float ax = a->x;
  float ay = a->y;
  float az = a->z;
  float aw = a->w;

  float bx = sinf(angle);
  float bw = cosf(angle);
  
  out->x = ax * bw + aw * bx;
  out->y = ay * bw + az * bx;
  out->z = az * bw - ay * bx;
  out->w = aw * bw - ax * bx;
  return out;
}

quat *quat_rotate_y(quat *out, const quat *a, float angle) {
  angle *= .5f;

  float ax = a->x;
  float ay = a->y;
  float az = a->z;
  float aw = a->w;

  float by = sinf(angle);
  float bw = cosf(angle);
  
  out->x = ax * bw - az * by;
  out->y = ay * bw + aw * by;
  out->z = az * bw + ax * by;
  out->w = aw * bw - ay * by;
  return out;
}

quat *quat_rotate_z(quat *out, const quat *a, float angle) {
  angle *= .5f;

  float ax = a->x;
  float ay = a->y;
  float az = a->z;
  float aw = a->w;

  float bz = sinf(angle);
  float bw = cosf(angle);
  
  out->x = ax * bw + ay * bz;
  out->y = ay * bw - ax * bz;
  out->z = az * bw + aw * bz;
  out->w = aw * bw - az * bz;
  return out;
}

quat *quat_calculate_w(quat *out, const quat *a) {
  float x = a->x;
  float y = a->y;
  float z = a->z;

  out->x = x;
  out->y = y;
  out->z = z;
  out->w = sqrtf(fabsf(1.f - x * x - y * y - z * z));
  return out;
}

quat *quat_add(quat *out, const quat *a, const quat *b) {
  return (quat *) vec4_add((vec4 *) out, (const vec4 *) a, (const vec4 *) b);
}

quat *quat_scale(quat *out, const quat *a, float b) {
  return (quat *) vec4_scale((vec4 *) out, (const vec4 *) a, b);
}

float quat_dot(const quat *a, const quat *b) {
  return vec4_dot((const vec4 *) a, (const vec4 *) b);
}

quat *quat_lerp(quat *out, const quat *a, const quat *b, float t) {
  return (quat *) vec4_lerp((vec4 *) out, (const vec4 *) a, (const vec4 *) b, t);
}

quat *quat_slerp(quat *out, const quat *a, const quat *b, float t) {
  // benchmarks:
  //    http://jsperf.com/quaternion-slerp-implementations
  float ax = a->x;
  float ay = a->y;
  float az = a->z;
  float aw = a->w;
  float bx = b->x;
  float by = b->y;
  float bz = b->z;
  float bw = b->w;

  float omega, cosom, sinom, scale0, scale1;

  // calc cosine
  cosom = ax * bx + ay * by + az * bz + aw * bw;

  // adjust signs (if necessary)
  if (cosom < 0.f) {
    cosom = -cosom;
    bx = -bx;
    by = -by;
    bz = -bz;
    bw = -bw;
  }

  // calculate coefficients
  if ((1.f - cosom) > MMATH_EPSILON) {
    // standard case (slerp)
    omega  = acosf(cosom);
    sinom  = sinf(omega);
    scale0 = sinf((1.f - t) * omega) / sinom;
    scale1 = sinf(t * omega) / sinom;
  } else {
    // "from" and "to" quaternions are very close
    //  ... so we can do a linear interpolation
    scale0 = 1.f - t;
    scale1 = t;
  }

  // calculate final values
  out->x = scale0 * ax + scale1 * bx;
  out->y = scale0 * ay + scale1 * by;
  out->z = scale0 * az + scale1 * bz;
  out->w = scale0 * aw + scale1 * bw;
  return out;
}

float quat_length(const quat *a) {
  return vec4_length((const vec4 *) a);
}

float quat_length_squared(const quat *a) {
  return vec4_length_squared((const vec4 *) a);
}

quat *quat_random(quat *out) {
  // Implementation of http://planning.cs.uiuc.edu/node198.html
  // TODO: Calling random 3 times is probably not the fastest solution

  float u1 = mmath_random();
  float u2 = mmath_random();
  float u3 = mmath_random();
  
  float sqrt1MinusU1 = sqrtf(1 - u1);
  float sqrtU1 = sqrtf(u1);

  out->x = sqrt1MinusU1 * sinf(2.f * (float) M_PI * u2);
  out->y = sqrt1MinusU1 * cosf(2.f * (float) M_PI * u2);
  out->z = sqrtU1 * sinf(2.f * (float) M_PI * u3);
  out->w = sqrtU1 * cosf(2.f * (float) M_PI * u3);
  return out;
}

quat *quat_normalize(quat *out, const quat *a) {
  return (quat *) vec4_normalize((vec4 *) out, (vec4 *) a);
}

quat *quat_invert(quat *out, const quat *a) {
  float ax = a->x;
  float ay = a->y;
  float az = a->z;
  float aw = a->w;

  float dot = ax * ax + ay * ay + az * az + aw * aw;

  if (dot == 0) {
    out->x = out->y = out->z = out->w = 0;
  } else {
    float inv_dot = 1.f / dot;

    out->x = -ax * inv_dot;
    out->y = -ay * inv_dot;
    out->z = -az * inv_dot;
    out->w =  aw * inv_dot;
  }

  return out;
}

quat *quat_conjugate(quat *out, const quat *a) {
  out->x = -a->x;
  out->y = -a->y;
  out->z = -a->z;
  out->w =  a->w;
  return out;
}

quat *quat_from_mat3(quat *out, const mat3 *m) {
  // Algorithm in Ken Shoemake's article in 1987 SIGGRAPH course notes
  // article "Quaternion Calculus and Fast Animation".

  float fTrace = m->data[0] + m->data[4] + m->data[8];
  float fRoot;
  if (fTrace > 0.f) {
    // |w| > 1/2, may as well choose w > 1/2
    fRoot = sqrtf(fTrace + 1.f);  // 2w
    out->w = .5f * fRoot;
    fRoot = .5f / fRoot;  // 1/(4w)
    
    out->x = (m->data[5] - m->data[7]) * fRoot;
    out->y = (m->data[6] - m->data[2]) * fRoot;
    out->z = (m->data[1] - m->data[3]) * fRoot;
  } else {
    // |w| <= 1/2
    int i = 0;
    if (m->data[4] > m->data[0]) {
      i = 1;
    }
    if (m->data[8] > m->data[i * 3 + i]) {
      i = 2;
    }

    int j = (i + 1) % 3;
    int k = (i + 2) % 3;
    fRoot = sqrtf(m->data[i * 3 + i] - m->data[j * 3 + j] - m->data[k * 3 + k] + 1.f);
    out->data[i] = .5f * fRoot;
    fRoot = .5f / fRoot;
    out->data[3] = (m->data[j * 3 + k] - m->data[k * 3 + j]) * fRoot;
    out->data[j] = (m->data[j * 3 + i] + m->data[i * 3 + j]) * fRoot;
    out->data[k] = (m->data[k * 3 + i] + m->data[i * 3 + k]) * fRoot;
  }

  return out;
}

quat *quat_from_euler(quat *out, float x, float y, float z) {
  static float half_to_rad = .5f * (float) M_PI / 180.f;
  x *= half_to_rad;
  y *= half_to_rad;
  z *= half_to_rad;
  
  float sx = sinf(x);
  float cx = cosf(x);
  float sy = sinf(y);
  float cy = cosf(y);
  float sz = sinf(z);
  float cz = cosf(z);
  
  out->x = sx * cy * cz - cx * sy * sz;
  out->y = cx * sy * cz + sx * cy * sz;
  out->z = cx * cy * sz - sx * sy * cz;
  out->w = cx * cy * cz + sx * sy * sz;
  return out;
}

bool quat_exact_equals(const quat *a, const quat *b) {
  return vec4_exact_equals((const vec4 *) a, (const vec4 *) b);
}

bool quat_equals(const quat *a, const quat *b) {
  return vec4_equals((const vec4 *) a, (const vec4 *) b);
}
