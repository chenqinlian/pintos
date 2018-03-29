

typedef int fixed_t;


#define P 17
#define Q 14

#define F (1 << Q)
#define REAL_MAX ((1 << 31) - 1)


/* Get integer part of a fixed-point value. */
#define CONVERT_TO_FIXED_POINT(n)       n * F

/* Get integer part of a fixed-point value. */
#define CONVERT_TO_INTEGER_ZERO(x) (x / F)

/* Get rounded integer of a fixed-point value. */
#define CONVERT_TO_INTEGER_NEAREST(x) (x >= 0 ? ((x + (F/2)) /F) : ((x - (F/2)) /F))



/* 16 LSB used for fractional part. */
#define FP_SHIFT_AMOUNT 16

/* Some helpful macros. */
/* Convert a value to fixed-point value. */
#define FP_CONST(n) ((fixed_t)(n *F))

/* Add two fixed-point value. */
#define ADD(x,y) (x + y)

/* Add a fixed-point value A and an int value B. */
#define ADD_INT(x,n) (x + (n * F))

/* Substract two fixed-point value. */
#define SUB(x,y) (x - y)

/* Substract an int value B from a fixed-point value A */
#define SUB_INT(x,n) (x - (n * F))

/* Multiply a fixed-point value A by an int value B. */
#define MUL_INT(x,n) (x * n)

/* Divide a fixed-point value A by an int value B. */
#define DIV_INT(x,n) (x / n)

/* Multiply two fixed-point value. */
#define MUL(x,y) ((fixed_t)(((int64_t) x) * y / F))

/* Divide two fixed-point value. */
#define DIV(x,y) ((fixed_t)((((int64_t) x) * F) / y))



