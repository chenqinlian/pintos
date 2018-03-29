/* Fixed-Point Real Arithmetic
The fundamental idea is to treat the rightmost bits of an integer as representing a fraction.
For example, we can designate the lowest 14 bits of a signed 32-bit integer as fractional bits,
so that an integer x represents the real number x/(2**14), where ** represents exponentiation.
This is called a 17.14 fixed-point number representation,
because there are 17 bits before the decimal point, 14 bits after it, and one sign bit.

 */

typedef int fixed_t;


#define P 17
#define Q 14

#define F (1 << Q)
#define REAL_MAX ((1 << 31) - 1)


/* Convert a value to fixed-point value. */
#define CONVERT_TO_FIXED_POINT(n) 	((fixed_t)(n *F))

/* Get integer part of a fixed-point value. */
#define CONVERT_TO_INTEGER_ZERO(x) 	(x / F)

/* Get rounded integer of a fixed-point value. */
#define CONVERT_TO_INTEGER_NEAREST(x) 	(x >= 0 ? ((x + (F/2)) /F) : ((x - (F/2)) /F))


/* Add         within two fixed-point value. */
#define ADD(x,y) 			(x + y)

/* Subtraction within two fixed-point value. */
#define SUB(x,y) 			(x - y)

/* Add int x  to fixed-point n. */
#define ADD_INT(x,n) 			(x + (n * F))

/* Subtract int x  by fixed-point n. */
#define SUB_INT(x,n) 			(x - (n * F))

/* Multiply    within two fixed-point value */
#define MUL(x,y) 			((fixed_t)(((int64_t) x) * y / F))

/* Multiply    fixed-point x with int n */
#define MUL_INT(x,n) 			(x * n)

/* Division    within two fixed-point value. */
#define DIV(x,y) 			((fixed_t)((((int64_t) x) * F) / y))

/* Divide     fixed-point x  by int n */
#define DIV_INT(x,n) 			(x / n)



