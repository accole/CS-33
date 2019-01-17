//Adam Cole

//fpwr4.c

//2.90:


//use a union to hold the data of an integer
//but be able to return those bits as a float
typedef union {
  float f;
  int i;
} floatunion;

//converts a unsigned int to a float
static float u2f(unsigned u){
  floatunion x;
  x.i = u;
  return x.f;
}

//returns 4^x as a float
float fpwr4(int x){
  //exponent and fraction bits
  unsigned exp, frac;
  //result variable
  unsigned u;
  if (x < -74){
    //too small, return 0.0
    exp = 0;
    frac = 0;
  } else if (x < -63){
    //denormalized result
    exp = 0;
    frac = (1 << (23 + 2*x + 126));
  } else if (x < 64){
    //normalized result
    exp = 2*x + 127;
    frac = 0;
  } else {
    //too big, return +infinity
    exp = 255;
    frac = 0;
  }
  //pack exp and frac into 32 bits
  u = exp << 23 | frac;
  //return result as a float
  return u2f(u);
}
