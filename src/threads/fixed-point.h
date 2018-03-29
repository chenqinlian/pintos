

/* Basic definitions of fixed point. */
typedef int fixed_t;


#define P 17
#define Q 14

#define F (1 << Q)
#define REAL_MAX ((1 << 31) - 1)

/* Convert n to fixed point*/
#define CONVERT_TO_FIXED_POINT(n)       n * F

/* Convert x to integer (rounding toward zero) */
#define CONVERT_TO_INTEGER_ZERO(x)      x / F

/* Convert x to integer (rounding to nearest) */
#define CONVERT_TO_INTEGER_NEAREST(x)   x >= 0 ? (x + F/2)/F : (x - F/2)/F




/* Add         within two fixed-point value. */
#define ADD(x, y)             x + y

/* Subtraction within two fixed-point value. */
#define SUB(x, y)             x - y

/* Add int x  to fixed-point n. */
#define ADD_INT(x, n)         x + n * F


/* Subtract int x  by fixed-point n. */
#define SUB_INT(x, n)         x - n * F

/* Multiply    within two fixed-point value */
#define MUL(x, y)             (int64_t)x * y / F

/* Multiply    fixed-point x with int n */
#define MUL_INT(x, n)         x * n

/* Division    within two fixed-point value. */
#define DIV(x, y)             (int64_t)x * F / y

/* Divide     fixed-point x  by int n */
#define DIV_INT(x, n)         x / n
