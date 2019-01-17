#include <limits.h>

int saturating_add(int x, int y){
  int maxmin = (x>>31)^INT_MAX;
  return __builtin_add_overflow_p (x, y, (__typeof__((x)+(y))) 0)? maxmin: x+y;
}
