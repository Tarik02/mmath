#include "mmath/common.h"
#include "mmath_private.h"

float mmath_random() {
  return (float) rand() / (float) RAND_MAX;
}
