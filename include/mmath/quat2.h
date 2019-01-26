#ifndef MMATH_QUAT2_H
#define MMATH_QUAT2_H

#include "mmath.h"

#pragma pack(push,1)
typedef union quat2 {
  float data[8];
  struct { float x1, y1, z1, w1, x2, y2, z2, w2; };
} quat2;
#pragma pack(pop)

#endif // MMATH_QUAT2_H
