/**
 * @brief Contains function type definitions and some utility functions for primitives and strings
 * commonly used with some data structures.
 *
 * @file utilities.c
 */

#include "utilities.h"

#include "dbg.h"
#include "macros.h"

#include <float.h>
#include <inttypes.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Maximum length of a string containing a pointer.
 */
#define MAX_POINTER_LEN (2 + (int) ceil(log2((double) UINTPTR_MAX) / 4))

/**
 * @brief Maximum length of a string containing a double.
 * Only the digits of precision are taken.
 * @details Since we are representing the double using the %g format specifier,
 * the number of characters is the sum of:
 * * 1 for the sign if the number is negative
 * * DBL_DIG digits
 * * 1 dot
 * * 2 characters for exponent notation
 * * Number of digits of the exponent
 */
#define MAX_DOUB_LEN (1 + DBL_DIG + 1 + 2 + (int) ceil(log10(DBL_MAX_10_EXP)))

/**
 * @brief Maximum length of a string containing a signed long.
 */
#define MAX_LONG_LEN (1 + (int) ceil(log10((double) LONG_MAX)))

/**
 * @brief Maximum length of a string containing a character.
 */
#define MAX_CHAR_LEN 1

/**
 * @brief Maximum length of a string containing a signed integer.
 */
#define MAX_INT_LEN (1 + (int) ceil(log10(INT_MAX)))

/* SECTION - Printing functions */

int util_generic_print(FILE *file, const void *p)
{
	/* The pointer is not directly printed, since the C standard isn't too clear about the behavior of
	 * fprintf with NULL pointers. It works totally fine with gcc though.
	 * See https://stackoverflow.com/questions/44996471/printing-null-pointers-with-p-is-undefined-behavior?rq=3
	 */
	ASSERT(file != NULL);

	if (!p) {
		return fprintf(file, "%s ", DEF_NULL);
	}

	return fprintf(file, "0x%" PRIxPTR, (uintptr_t) p);
}

int util_char_print(FILE *file, const void *c)
{
	ASSERT(file != NULL);

	if (!c) {
		return fprintf(file, "%s ", DEF_NULL);
	}

	return fprintf(file, "%c ", *(const char *) c);
}

int util_int_print(FILE *file, const void *i)
{
	ASSERT(file != NULL);

	if (!i) {
		return fprintf(file, "%s ", DEF_NULL);
	}

	return fprintf(file, "%d ", *(const int *) i);
}

int util_double_print(FILE *file, const void *d)
{
	ASSERT(file != NULL);

	if (!d) {
		return fprintf(file, "%s ", DEF_NULL);
	}

	return fprintf(file, "%.*g", DBL_DIG, *(const double *) d);
}

int util_string_print(FILE *file, const void *s)
{
	ASSERT(file != NULL);

	if (!s) {
		return fprintf(file, "%s ", DEF_NULL);
	}

	return fprintf(file, "%s ", (const char *) s);
}

/* !SECTION */
/* SECTION - Comparison functions */
/* Rationale behind the null return values: We consider that null values should be ordered
 * before all other elements. Mathematically, this preserves the properties of total
 * orders, i.e, reflexive, antisymmetric, transitive and all elements can be compared
 * against each other.
 *
 * If, for some reason, some data structure happens to accept null values as data, their order
 * will not be broken when using these functions.
 */

int util_char_cmp(const void *char1, const void *char2)
{
	if (!char1 || !char2) {
		// One-liner that returns -1, 0 or 1 accordingly when one is null
		return (!char1 < !char2) - (!char1 > !char2);
	}

	return *(const char *) char1 - *(const char *) char2; // Sort according to ASCII code
}

int util_int_cmp(const void *int1, const void *int2)
{
	if (!int1 || !int2) {
		return (!int1 < !int2) - (!int1 > !int2);
	}

	int i1 = *(const int *) int1;
	int i2 = *(const int *) int2;

	return (i1 > i2) - (i1 < i2);
}

int util_double_cmp(const void *double1, const void *double2)
{
	if (!double1 || !double2) {
		return (!double1 < !double2) - (!double1 > !double2);
	}

	double d1 = *(const double *) double1;
	double d2 = *(const double *) double2;

	return (d1 > d2) - (d1 < d2);
}

int util_string_cmp(const void *str1, const void *str2)
{
	if (!str1 || !str2) {
		return (!str1 < !str2) - (!str1 > !str2);
	}

	return strcmp((const char *) str1, (const char *) str2);
}

/* !SECTION */
/* SECTION - To string functions */

char *util_generic_to_string(const void *elem)
{
	char *str;

	if (!elem) {
		return NULL;
	}

	str = malloc((MAX_POINTER_LEN + 1) * sizeof(char));
	check_mem(str);

	snprintf(str, MAX_POINTER_LEN + 1, "0x%" PRIxPTR, (uintptr_t) elem);

error:
	return str;
}

char *util_char_to_string(const void *c)
{
	char *str;

	if (!c) {
		return NULL;
	}

	str = malloc((MAX_CHAR_LEN + 1) * sizeof(char));
	check_mem(str);

	str[0] = *(const char *) c;
	str[1] = '\0';

error:
	return str;
}

char *util_int_to_string(const void *n)
{
	char *str;

	if (!n) {
		return NULL;
	}

	str = malloc((MAX_INT_LEN + 1) * sizeof(char));
	check_mem(str);

	snprintf(str, MAX_INT_LEN + 1, "%d", *(const int *) n);

error:
	return str;
}

char *util_double_to_string(const void *d)
{
	char *str;

	if (!d) {
		return NULL;
	}

	str = malloc((MAX_DOUB_LEN + 1) * sizeof(char));
	check_mem(str);

	snprintf(str, MAX_DOUB_LEN + 1, "%.*g", DBL_DIG, *(const double *) d);

error:
	return str;
}

char *util_string_to_string(const void *s)
{
	char *str;

	if (!s) {
		return NULL;
	}

	str = strdup((const char *) s);
	check_mem(str);

error:
	return str;
}

/* !SECTION */
/* SECTION - From string functions */

void *util_char_from_string(const char *str)
{
	ASSERT(str != NULL);

	char *c = malloc(sizeof(char));
	check_mem(c);

	*c = *str;

error:
	return c;
}

void *util_int_from_string(const char *str)
{
	ASSERT(str != NULL);

	int *i = malloc(sizeof(int));
	check_mem(i);

	char *end;
	errno    = 0;
	long tmp = strtol(str, &end, 10);
	if (tmp > INT_MAX || tmp < INT_MIN) {
		errno = ERANGE;
	}
	check(errno == 0, "Error parsing %s", str);
	check(end != str, "No integer could be parsed from %s", str);

	*i = (int) tmp;

	return i;

error:
	free(i);
	return NULL;
}

void *util_double_from_string(const char *str)
{
	ASSERT(str != NULL);

	double *d = malloc(sizeof(double));
	check_mem(d);

	char *end;
	errno = 0;
	*d    = strtod(str, &end);
	check(errno == 0, "Error parsing %s", str);
	check(end != str, "No value could be parsed from %s", str);

	return d;

error:
	free(d);
	return NULL;
}

void *util_string_from_string(const char *str)
{
	ASSERT(str != NULL);

	char *s = strdup(str);
	check_mem(s);

error:
	return s;
}

/* !SECTION */
/* SECTION - Misc */

void util_string_free(void *str)
{
	if (str) {
		free(*(char **) str);
		free(str);
	}
}

/* !SECTION */
