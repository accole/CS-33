#include <limits.h>

int saturating_add(int x, int y){
  // INT_MIN == 1000 0000 0000 0000 0000 0000 0000 0000
  // INT_MAX == 0111 1111 1111 1111 1111 1111 1111 1111
  // signed binary representation of the sum
  int sum = x + y;
  // used to see if both x and y are both + or -
  // by &ing what both x and y have different than the sum,
  // we can tell if there will be overflow by whether or not
  // a 1 will be the most significant digit, since its only if
  // the two inputs' signs are different than the sum's, but the
  // same as each others' when overflow occurs.
  int check = (x^sum)&(y^sum);
  // if x or y (only need to use one, assuming they are the same),
  // is negative, then the sum will have negative overflow, and 
  // vice versa.  therefore x>>31 will = 1111 1111 1111 1111 1111 .... 
  // if x is negative and will =  0000 0000 0000 0000 0000 0000 ....
  // if x is positive.  By exclusive or-ing x>>31 against INT_MAX,
  // the result will be INT_MAX if x is positive and INT_MIN if x 
  // is negative.
  int overflow = (x>>31)^ INT_MAX;
  // if check is negative, theres overflow.  otherwise return the sum
  return check < 0? overflow: sum;
}
