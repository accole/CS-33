#include <limits.h>

unsigned long srl (unsigned long x, int k) { 
  //type cast the unsigned long x to a signed integer so the
  //compiler inherently performs an arithmetic shift right
  //Then, type cast the result to an unsigned long because that
  //is the return type.  then return the value with the addition of
  //k zeros where the shift was performed.  Do this by using the &
  //operator of the complement of -1 (all zeros) of the length of the
  //long, so that it ends in a logical shift right.
  unsigned long xsra = (long)x >> k;
  //return logical right shift
  return xsra&~(-1<<((8*sizeof(long))-k));
}

long sra(long x, int k) {
  //same as above, except use or, so that the k values of -1 fill in
  //the most significant bits to perform the arithmetic shift.  But ONLY
  //if the x value was negative, hence 1 being the most significant bit
  long xsrl = (unsigned long) x>>k;
  //return arithmetic shift right
  return x<0?xsrl|(-1<<((8*sizeof(long)-k))):xsrl;
}
