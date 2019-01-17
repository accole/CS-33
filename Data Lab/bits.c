/* 
 * C:APP Data Lab 
 *
 * Adam Cole
 *  
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
   //by dividing the orginal input by 2 repeatedly
   //until only one bit remains, and using the & operator
   //to preserve any 1's, the final variable u will have
   //a 1 if any ones appeared, and a 0 if the number was 0.
   //by complementing this, and &ing it with 1, we get the desired result
   int y = (x|(x>>16));
   y = (y|(y>>8));
   y = (y|(y>>4));
   y = (y|(y>>2));
   y = (y|(y>>1));
   return ~y&1;
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
  //use logarithmic operations to solve using less operations
  //hint from TA: parallelism
  //create masks in order to count bits in every 2-bit pair, then 
  //every byte, etc. until the entire integer is represented.
  int mm1, m1, mm2, m2, mm3, m3, m4, m5, n;
  mm1 = (0x55<<8)+0x55;   
  m1 = mm1 +(mm1<<16);  //01010101010101....
  mm2 = (0x33 << 8) + 0x33;
  m2 = mm2 + (mm2 <<16);//0011001100110011....
  mm3 = (0x0f <<8) + 0x0f;
  m3 = mm3 + (mm3 << 16);//0000....111100001111
  m4 = (0xff << 16) + 0xff;//000000011111111000000011111111
  m5 = (0xff << 8) + 0xff;//000.....1111111111111111
  
  //makes adding the bits together "vertical"
  n = (x & m1)+((x>>1)& m1);
  n = (n & m2) + ((n>>2)& m2);
  n = (n & m3) + ((n>>4)& m3);
  n = (n & m4) + ((n>>8)& m4);
  return (n & m5) + ((n>>16)& m5);
}
/* 
 * bitOr - x|y using only ~ and & 
 *   Example: bitOr(6, 5) = 7
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitOr(int x, int y) {
  //in order to "or" the two bits, complement both x and y.
  //therefore, when we & the two, only the bits where both
  //integers have 1's will remain (before the complement, 0's).
  //this will leave any bits that both have 0 or a mismatch as 0,
  //and the complement of this will return them as 1's.
  return ~((~x)&(~y));
}
/*
 * bitRepeat - repeat x's low-order n bits until word is full.
 *   Can assume that 1 <= n <= 32.
 *   Examples: bitRepeat(1, 1) = -1
 *             bitRepeat(7, 4) = 0x77777777
 *             bitRepeat(0x13f, 8) = 0x3f3f3f3f
 *             bitRepeat(0xfffe02, 9) = 0x10080402
 *             bitRepeat(-559038737, 31) = -559038737
 *             bitRepeat(-559038737, 32) = -559038737
 *   Legal ops: int and unsigned ! ~ & ^ | + - * / % << >>
 *             (This is more general than the usual integer coding rules.)
 *   Max ops: 40
 *   Rating: 4
 */
int bitRepeat(int x, int n) {
  //we extract the bits to be repeated by creating a mask that will only keep
  // the first n bits.  Then we use logarithmic shifts to apply the first
  // n bits to the rest of the 32 bit integer.
  int logshift;
  unsigned m;
  m = x<<(32-n);
  m = (m|0)>>(32-n);
  logshift = (1<<(!((n)>>5)*n))|1;
  logshift = (logshift << (!((n*2)>>5)*(n*2)))|logshift;
  logshift = (logshift << (!((n*4)>>5)*(n*4)))|logshift;
  logshift = (logshift << (!((n*8)>>5)*(n*8)))|logshift;
  return ((logshift << (!((n*16)>>5)*(n*16)))|logshift) * m;
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
  //by adding the complement on n to 33, we calculate
  //how many bits remain after using the first 'n', since
  // -n = ~(n)+1, and 32 - n gives us this value.
  //then in order to fill all the y higher
  //order bits with the sign bit, we shift x << y and then back, and 
  //then we test thatz and x are == by using bitwise operators.
  int y, z;
  y = 33 + ~(n);
  z = (x<<y)>>y;
  return !(z^x);
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
  //we want to get the nth byte at the first 4 bits of x.
  //we multiply n bytes by 8 bits by left shifting n << 3,
  //and then we left shift x by that many bits to get them at the 
  //4 least significant bits.  then, & this with 0xff to return only
  //the 8 least significant bits.
  return (x>>(n<<3))&(0xff);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  //to test all the different conditional cases, we create ints to
  //hold true(1)/false(0) and create one logical return statement
  //to make a correct condition test.  For x to be less than or equal
  //to y, x can never be positive while y is negative.  Therefore, xpos!
  //is required for all cases in our return statement.  Futhermore,
  //any of the following cases will imply x<=y:
  //   they are equal, y is positive and x is negative, or x and y have the
  //   same sign, but the sign of the difference between the two is not
  //   negative.
  int xsign = x>>31;
  int ysign = y>>31;
  int opp = ((x>>31)^(y>>31));
  
  int equal = !(x^y);
  int ypos = opp & xsign;
  int xpos = opp & ysign;

  int signdiff = !((y + ~x + 1)>>31);
  return (ypos|equal|((!ypos) & signdiff))& !xpos;
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
  //use a mask to only get the most significant digit in x (sign bit)
  //then not that whole thing because the instructions specify that for
  //positives we want to return 1, and not the other way around.  check
  //for 0 by double notting x and including it in the condition.
  return ((!((1<<31)& x)) & !!x);
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
  //create a mask of 0000...11111 where the 0's extend for n 0's.
  //then & this against the arithmetically shifted number to get
  //a logical right shift.
  int y = (1<<31)>>n;
  return ~(y<<1)&(x>>n);
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  //return the most minimum value, 0x800000...
  return (1<<31);
}
