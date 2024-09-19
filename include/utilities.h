/**
 * @brief Contains function type definitions and some utility functions for primitives and strings
 * commonly used with some data structures.
 *
 * @file utilities.h
 */

#ifndef UTILITIES_H
#define UTILITIES_H

#define _POSIX_C_SOURCE 200809L

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
typedef int (*util_print_fn)(FILE *file, const void *elem);

/**
 * @brief Function type to compare two elements.
 *
 * @param elem1 Pointer to the first element.
 * @param elem2 Pointer to the second element.
 *
 * @return A negative integer, zero, or a positive integer as elem1
 * is less than, equal to, or greater than elem2.
 * NULL is always ordered before any other element, and is always equal to itself.
 */
typedef int (*util_compare_fn)(const void *elem1, const void *elem2);

/**
 * @brief Function type to convert an element to a string.
 *
 * @param elem Element to convert to string.
 *
 * @return String that represents the element. String is malloc'ed and must be freed after use.
 * NULL is returned if the element is NULL or if malloc fails.
 */
typedef char *(*util_to_string_fn)(const void *elem);

/**
 * @brief Function type to convert strings to elements.
 *
 * @param str String with the element. Must not be NULL.
 *
 * @return Element converted from string.
 * Element is malloc'ed. The element must be freed with its respective free function
 * (free() may be used for primitive types and util_string_free() for strings)
 * NULL is returned if malloc fails or if the string could not be parsed.
 */
typedef void *(*util_elem_from_string_fn)(const char *str);

/**
 * @brief Function type to free an element
 *
 * @param elem Element to free. NULL is no-op.
 */
typedef void (*util_free_fn)(void *elem);

/* !SECTION */
/* SECTION - Printing functions */

/**
 * @brief Print the memory address of a given pointer, followed by a space.
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
 *
 * @param file A pointer to the stream. Must not be NULL.
 * @param i A pointer to the integer to print (base 10). @ref DEF_NULL is printed if NULL.
 * @return Number of bytes printed.
 * Returns a negative number if there were errors while printing
 */
int util_int_print(FILE *file, const void *i);

/**
 * @brief Print a double precision value (using %g specifier), followed by a space.
 *
 * @param file A pointer to the stream. Must not be NULL.
 * @param d A pointer to the value to print (base 10). @ref DEF_NULL is printed if NULL.
 * @return Number of bytes printed.
 * Returns a negative number if there were errors while printing
 */
int util_double_print(FILE *file, const void *d);

/**
 * @brief Print a string, followed by a space.
 *
 * @param file A pointer to the stream. Must not be NULL.
 * @param s A pointer to the string to print. @ref DEF_NULL is printed if NULL.
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
 * @param str1 Pointer to the first string.
 * @param str2 Pointer to the second string.
 * @return A negative integer, zero, or a positive integer as str1
 * is less than, equal to, or greater than the specified str2.
 * NULL is always ordered before any other element, and is always equal to itself.
 */
int util_string_cmp(const void *str1, const void *str2);

/* !SECTION */
/* SECTION - Conversion to string functions */

/**
 * @brief Converts the address of an element to a string.
 *
 * @param e Pointer to print.
 * @return String with the pointer address. Must be freed after use.
 * NULL is returned if the element is NULL or if malloc fails (use errno to know which one).
 */
char *util_generic_to_string(const void *e);

/**
 * @brief Converts a signed character to a string.
 *
 * @param c Pointer to the character.
 * @return String with the printed character. Must be freed after use.
 * NULL is returned if the element is NULL or if malloc fails (use errno to know which one).
 */
char *util_char_to_string(const void *c);

/**
 * @brief Converts a signed integer to a string.
 *
 * @param i Pointer to the integer.
 * @return String with the printed integer (base 10). Must be freed after use.
 * NULL is returned if the element is NULL or if malloc fails (use errno to know which one).
 */
char *util_int_to_string(const void *i);

/**
 * @brief Converts a double precision value to a string.
 *
 * @param d Pointer to the value.
 * @return String with the printed double (base 10). Must be freed after use.
 * NULL is returned if the element is NULL or if malloc fails (use errno to know which one).
 */
char *util_double_to_string(const void *d);

/**
 * @brief Converts a string given its pointer to a string.
 *
 * @param s Pointer to the string.
 * @return Copy of the string provided. Must be freed after use.
 * NULL is returned if the element is NULL or if malloc fails (use errno to know which one).
 */
char *util_string_to_string(const void *s);

/* !SECTION */
/* SECTION - String parsing functions */

/**
 * @brief Creates a character from a string.
 *
 * @param str Pointer to the char. Must not be NULL.
 * Later characters are ignored.
 * @return Pointer to the character created. Must be freed after use.
 * NULL is returned if malloc fails or if the string could not be parsed.
 */
void *util_char_from_string(const char *str);

/**
 * @brief Creates an integer from a string.
 *
 * @param str String with the integer (base 10). Must not be NULL.
 * Trailing characters after the number are ignored. Parsing is done with strtol().
 * @return Pointer to the integer created. Must be freed after use.
 * NULL is returned if malloc fails or if the string could not be parsed.
 */
void *util_int_from_string(const char *str);

/**
 * @brief Creates a double from a string.
 *
 * @param str String with the double (base 10, using %g specifier). Must not be NULL.
 * Trailing characters after the number are ignored. Parsing is done with strtod().
 * @return Pointer to the double created. Must be freed after use.
 * NULL is returned if malloc fails or if the string could not be parsed.
 */
void *util_double_from_string(const char *str);

/**
 * @brief Duplicates a string.
 *
 * @param str String to duplicate. Must not be NULL.
 * @return *Pointer* to the duplicated string. Must be freed after use.
 * NULL is returned if malloc fails or if the string could not be copied.
 */
void *util_string_from_string(const char *str);

/* !SECTION */
/* SECTION - Misc */

/**
 * @brief Frees a pointer to a string and its content.
 * ~~Meant to be used together with util_string_from_string() and similar.~~
 * @deprecated Useless after reducing indirection in other string functions.
 *
 * @param str String to free. NULL is no-op.
 */
void util_string_free(void *str);

/* !SECTION */

#endif
