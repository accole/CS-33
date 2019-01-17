#define R  7
#define S  5
#define T  8

long A[R][S][T];

long
ele (long i, long j, long k)
{
  return A[R - i][1 - j][k - 1];
}

/*
1) extend equation 3.1

T D[R][S][T] 
& A[i][j][k] = A + L( (i*S*T) + (j*T) + k )
since to calculate the number of bits to the
i,j,kth element, you add the number of bits that
you pass after A[i][0][0] after A[0][j][0] , and 
after A[0][0][k] bits from the start of the array.

2) after expanding the machine instructions in the 
given ele.s, we find that the calculations the
compiler makes returns the value
     A = 320(R-i)-64(j)+8k+56.
we know the value of R because it is the first constant
loaded into the %eax register.  From there, we 
calculate T because the equivalence gives
     8*T*j = 64*j,
and then we find S through a similar method
     8*S*T*(R-i)=320*(R-i)
giving:

R = 7
S = 5
T = 8

*/
