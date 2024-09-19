/**
 * @brief Collection of useful and commonly used macros.
 *
 * @file macros.h
 */

#ifndef PERSONAL_MACROS_H
#define PERSONAL_MACROS_H

/* SECTION - Math */

/**
 * @brief Computes the minimum of two primitive types according to their natural order.
 */
#define MIN(a, b) \
	({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })

/**
 * @brief Computes the maximum of two primitive types according to their natural order.
 */
#define MAX(a, b) \
	({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

/**
 * @brief Compares two primitives according to their natural order.
 *
 * @details Returns:
 * * -1 if x < y
 * * 0 if x == y
 * * 1 if x > y
 */
#define COMPARE(x, y) (((x) > (y)) - ((x) < (y)))

/**
 * @brief Implementation of the signum function for primitive types.
 *
 * @details Returns:
 * * -1 if x < 0
 * * 0 if x == 0
 * * 1 if x > 0
 */
#define SIGN(x) COMPARE(X, 0)

/**
 * @brief Swaps the contents of two variables.
 */
#define SWAP(x, y)                 \
	do {                           \
		__typeof__(x) SWAP = x;    \
		x                  = y;    \
		y                  = SWAP; \
	} while (0)


/* !SECTION */

/* SECTION - LOOPS AND ARRAYS */

/**
 * @brief Never ending loop.
 */
#define FOREVER for (;;)

/**
 * @brief Incremental or decremental loop from start (inclusive) to end (exclusive).
 */
#define RANGE(i, start, end) for (i = (start); (((end) >= (start)) ? (i <= (end)) : (i >= (end))); \
								  (((end) >= (start)) ? ((i)++) : ((i)--)))

/**
 * @brief Enhanced loop for arrays only.
 */
#define FOR_EACH(i, A)                                               \
	for (int _keep = 1, _count = 0, _size = sizeof(A) / sizeof *(A); \
		 _keep && _count != _size;                                   \
		 _keep = !_keep, _count++)                                   \
		for (i = (A) + _count; _keep; _keep = !_keep)

/**
 * @brief Computes the length of an array.
 */
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(*(a)))

/* !SECTION */

/* SECTION - Strings */

/**
 * @brief String representation of NULL
 */
#define DEF_NULL "null"

/**
 * @brief Returns the empty string literal if s is NULL. Otherwise returns the string.
 */
#define EMPTY_IF_NULL(s) ((s) ? (s) : "")

/**
 * @brief Returns @ref DEF_NULL if s is NULL. Otherwise returns the string.
 */
#define DEF_IF_NULL(s) ((s) ? (s) : DEF_NULL)

/* !SECTION */

#endif
