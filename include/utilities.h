/**
 * @brief Contains function type definitions and some utility functions for primitives and strings
 * commonly used with some data structures.
 *
 * @file utilities.h
 */

#ifndef UTILITIES_H
#define UTILITIES_H

#define _POSIX_C_SOURCE 200809L // NOLINT

#include <stdbool.h>
#include <stdio.h>

/* SECTION - Function types */

/**
 * @brief Function type to print an element.
 *
 * @param file Stream to print to. Must not be NULL.
 * @param elem Element to print. @ref DEF_NULL is printed if NULL.
 *
 * @return Numbers of bytes printed. A negative number if there were errors while printing.
 */
typedef int (*util_print)(FILE *file, const void *elem);

/**
 * @brief Function type to compare two elements.
 *
 * @details The function type shall be consistent with a total order relation
 * (reflexive, symmetric, transitive, strong connectivity) over the set of values
 * that both elements can take, except possibly NULL.
 *
 * @param elem1 Pointer to the first element.
 * @param elem2 Pointer to the second element.
 *
 * @return A negative integer, zero, or a positive integer as elem1
 * is less than, equal to, or greater than elem2.
 */
typedef int (*util_compare)(const void *elem1, const void *elem2);

/**
 * @brief Function type to convert an element to a string.
 *
 * @details To reduce ambiguity with return values and simplify error handling,
 * one might not want NULL to be returned as the string for a null element. Instead,
 * special strings such as `null`, `NIL` or `NULL` could be used.
 * If one chooses to return string literals or preallocated strings, it is important
 * to modify the way the string is freed to avoid invalid calls to free().
 *
 * @param elem Element to convert to string.
 *
 * @return String that represents the element. String is malloc'ed and must be freed after use.
 * NULL is returned if the element is NULL (implementation defined) or if malloc fails.
 */
typedef char *(*util_toString)(const void *elem);

/**
 * @brief Function type to convert strings to elements.
 *
 * @details To reduce ambiguity with return values and simplify error handling,
 * NULL should not be returned as a valid element. Consider using a special null object instead.
 *
 * @param str String with the element. Must not be NULL.
 *
 * @return Element converted from string.
 * Element is malloc'ed. The element must be freed with its respective free function
 * (free() may be used for primitive types and util_string_free() for strings)
 * NULL is returned if malloc fails or if the string could not be parsed.
 */
typedef void *(*util_elemFromString)(const char *str);

/**
 * @brief Function type to free an element
 *
 * @param elem Element to free. NULL is no-op.
 */
typedef void (*util_free)(void *elem);

/**
 * @brief Function type that evaluates a predicate on the given element.
 * The test shall not modify the element.
 *
 * @param elem Element to test the boolean predicate on.
 *
 * @return `true` if the argument matches the predicate, `false` otherwise.
 */
typedef bool (*util_predicate)(const void *elem);

/**
 * @brief Function type that tests whether two elements are equal.
 *
 * @details The function type shall be consistent with an equivalence binary relation
 * (reflexive, symmetric and transitive) over the set of values that both elements can take,
 * except possibly NULL.
 *
 * It should also be consistent accross mutiple invocations: two elements are equal if and
 * only if this function returns `true` *always*.
 *
 * @param elem1 First element to compare.
 * @param elem2 Second element to compare.
 *
 * @return `true` if both elements are equal, `false` otherwise.
 */
typedef bool (*util_equal)(const void *elem1, const void *elem2);

/* !SECTION */
/* SECTION - Printing functions */

/**
 * @brief Print the memory address of a given pointer, followed by a space.
 * Format prints the memory address in an hexadecimal format, with leading '0X' and uppercase letters.
 *
 * @param file A pointer to the stream. Must not be NULL.
 * @param p The pointer to print. @ref DEF_NULL is printed if NULL.
 * @return Number of bytes printed.
 * Returns a negative number if there were errors while printing
 */
int util_generic_print(FILE *file, const void *p);

/**
 * @brief Print a char, followed by a space.
 *
 * @param file A pointer to the stream. Must not be NULL.
 * @param c A pointer to the char to print. @ref DEF_NULL is printed if NULL.
 * @return Number of bytes printed.
 * Returns a negative number if there were errors while printing
 */
int util_char_print(FILE *file, const void *c);

/**
 * @brief Print an integer, followed by a space.
 * Format uses %d specifier.
 *
 * @param file A pointer to the stream. Must not be NULL.
 * @param i A pointer to the integer to print (base 10). @ref DEF_NULL is printed if NULL.
 * @return Number of bytes printed.
 * Returns a negative number if there were errors while printing
 */
int util_int_print(FILE *file, const void *i);

/**
 * @brief Print a double precision value, followed by a space.
 * Format uses %g specifier and DBL_DIG significant digits.
 *
 * @param file A pointer to the stream. Must not be NULL.
 * @param d A pointer to the value to print. @ref DEF_NULL is printed if NULL.
 * @return Number of bytes printed.
 * Returns a negative number if there were errors while printing
 */
int util_double_print(FILE *file, const void *d);

/**
 * @brief Print a string, followed by a space.
 *
 * @param file A pointer to the stream. Must not be NULL.
 * @param s String to print. @ref DEF_NULL is printed if NULL.
 * @return Number of bytes printed.
 * Returns a negative number if there were errors while printing
 */
int util_string_print(FILE *file, const void *s);

/* !SECTION */
/* SECTION - Comparison functions */

/**
 * @brief Compare two characters according to their natural order in the ASCII table.
 *
 * @param char1 Pointer to the first character.
 * @param char2 Pointer to the second character.
 * @return A negative integer, zero, or a positive integer as char1
 * is less than, equal to, or greater than the specified char2.
 * NULL is always ordered before any other element, and is always equal to itself.
 */
int util_char_cmp(const void *char1, const void *char2);

/**
 * @brief Compare two integers.
 *
 * @param int1 Pointer to the first integer.
 * @param int2 Pointer to the second integer.
 * @return A negative integer, zero, or a positive integer as int1
 * is less than, equal to, or greater than the specified int2.
 * NULL is always ordered before any other element, and is always equal to itself.
 */
int util_int_cmp(const void *int1, const void *int2);

/**
 * @brief Compare two double precision values.
 *
 * @param double1 Pointer to the first value.
 * @param double2 Pointer to the second value.
 * @return A negative integer, zero, or a positive integer as double1
 * is less than, equal to, or greater than the specified double2.
 * NULL is always ordered before any other element, and is always equal to itself.
 */
int util_double_cmp(const void *double1, const void *double2);

/**
 * @brief Compare two strings.
 *
 * @param str1 First string.
 * @param str2 Second string.
 * @return A negative integer, zero, or a positive integer as str1
 * is less than, equal to, or greater than the specified str2.
 * NULL is always ordered before any other element, and is always equal to itself.
 */
int util_string_cmp(const void *str1, const void *str2);

/* !SECTION */
/* SECTION - Conversion to string functions */

/**
 * @brief Converts the address of an element to a string.
 * Format prints the memory address in an hexadecimal format, with leading '0x' and uppercase letters.
 *
 * @param e Pointer to print.
 * @return String with the pointer address. Must be freed after use.
 * NULL is returned if the element is NULL or if malloc fails (use errno to know which one).
 */
char *util_generic_toString(const void *e);

/**
 * @brief Converts a signed character to a string.
 *
 * @param c Pointer to the character.
 * @return String with the printed character. Must be freed after use.
 * NULL is returned if the element is NULL or if malloc fails (use errno to know which one).
 */
char *util_char_toString(const void *c);

/**
 * @brief Converts a signed integer to a string.
 *
 * @param i Pointer to the integer.
 * @return String with the printed integer. Must be freed after use.
 * Format uses %d specifier.
 * NULL is returned if the element is NULL or if malloc fails (use errno to know which one).
 */
char *util_int_toString(const void *i);

/**
 * @brief Converts a double precision value to a string.
 *
 * @param d Pointer to the value.
 * @return String with the printed double. Must be freed after use.
 * Format uses %g specifier and DBL_DIG significant digits.
 * NULL is returned if the element is NULL or if malloc fails (use errno to know which one).
 */
char *util_double_toString(const void *d);

/**
 * @brief Converts a string given its pointer to a string.
 *
 * @param s String.
 * @return Copy of the string provided. Must be freed after use.
 * NULL is returned if the element is NULL or if malloc fails (use errno to know which one).
 */
char *util_string_toString(const void *s);

/* !SECTION */
/* SECTION - String parsing functions */

/**
 * @brief Creates a character from a string.
 *
 * @param str Pointer to the char. Must not be NULL.
 * Later characters are ignored.
 * @return Pointer to the character created. Must be freed after use.
 * NULL is returned if malloc fails. In this case, the errno value is set.
 */
void *util_char_fromString(const char *str);

/**
 * @brief Creates an integer from a string.
 *
 * @param str String with the integer (base 10). Must not be NULL.
 * Trailing characters after the number are ignored. Parsing is done with strtol().
 * @return Pointer to the integer created. Must be freed after use.
 * NULL is returned if malloc fails or if the string could not be parsed.
 * In this case, the errno value is set. If errno is 0, no integer could be parsed.
 */
void *util_int_fromString(const char *str);

/**
 * @brief Creates a double from a string.
 *
 * @param str String with the double. Must not be NULL.
 * Trailing characters after the number are ignored. Parsing is done with strtod().
 * @return Pointer to the double created. Must be freed after use.
 * NULL is returned if malloc fails or if the string could not be parsed.
 * In this case, the errno value is set. If errno is 0, no value could be parsed.
 */
void *util_double_fromString(const char *str);

/**
 * @brief Duplicates a string.
 *
 * @param str String to duplicate. Must not be NULL.
 * @return Duplicated string. Must be freed after use.
 * NULL is returned if the string could not be copied. In this case, the errno value is set.
 */
void *util_string_fromString(const char *str);

/* !SECTION */
/* SECTION - Misc */

/**
 * @brief Test whether two pointers point to the same address.
 *
 * @param e1 First pointer.
 * @param e2 Second pointer.
 * @return true if e1 == e2, false otherwise.
 */
bool util_genericEqual(const void *e1, const void *e2);

/* !SECTION */

#endif
