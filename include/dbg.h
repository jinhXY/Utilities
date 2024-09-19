/**
 * @brief Collection of macros and enums useful for error handling and print debugging.
 *
 * @file dbg.h
 */

/* Taken from https://github.com/daviddao/debug-macros */

#ifndef DBG_H
#define DBG_H

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

/**
 * @brief Contains common error codes.
 */
typedef enum {
	OK,            /**< Successful execution */
	OUT_OF_MEMORY, /**< Ran out of memory */
	INVALID_ARG    /**< Invalid arguments provided to the function */
} Status;

/**
 * @brief Obtains the name of the file, including the extension.
 */
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)


#ifdef SILENT
	#define NDEBUG
#endif

#ifdef NDEBUG
	#define debug(M, ...)
	#define ASSERT(expr)

#else
	/**
	 * @brief Prints a debug message to `stderr`. Same format as printf.
	 */
	#define debug(M, ...) fprintf(stderr, "DEBUG %s:%d: " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)

	/**
	 * @brief Reimplementation of assert() that uses @ref __FILENAME__ instead of the file's
	 * full path. This is to omit the file prefix in released binaries with debug information.
	 */
	#define ASSERT(expr)                                                          \
		((void) sizeof((expr) ? 1 : 0), __extension__({                           \
			 if (expr)                                                            \
				 ; /* empty */                                                    \
			 else                                                                 \
				 __assert_fail(#expr, __FILENAME__, __LINE__, __ASSERT_FUNCTION); \
		 }))
#endif

/**
 * @brief Returns a string containing the status of errno.
 */
#define clean_errno() (errno == 0 ? "None" : strerror(errno))

#ifdef SILENT
	#define log_err(M, ...)
	#define log_warn(M, ...)
	#define log_info(M, ...)
#else
	/**
	 * @brief Prints an error message to `stderr`. Same format as printf.
	 */
	#define log_err(M, ...)  fprintf(stderr, "[ERROR] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)

	/**
	 * @brief Prints a warning message to `stderr`. Same format as printf.
	 */
	#define log_warn(M, ...) fprintf(stderr, "[WARN] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)

	/**
	 * @brief Prints an info message to `stderr`. Same format as printf.
	 */
	#define log_info(M, ...) fprintf(stderr, "[INFO] (%s:%d) " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#endif

/**
 * @brief Check if condition A is true. If it is, logs an error and jumps to error label for cleanup.
 */
#define check(A, M, ...)           \
	if (!(A)) {                    \
		log_err(M, ##__VA_ARGS__); \
		errno = 0;                 \
		goto error;                \
	}

/**
 * @brief Logs an error and jumps to error label. Meant for code regions that should *not* run.
 */
#define sentinel(M, ...)           \
	{                              \
		log_err(M, ##__VA_ARGS__); \
		errno = 0;                 \
		goto error;                \
	}

/**
 * @brief Checks if the pointer is not NULL using check()
 */
#define check_mem(A) check((A), "Out of memory.")

/**
 * @brief Same as check(), but logs a debug message instead of an error.
 */
#define check_debug(A, M, ...)   \
	if (!(A)) {                  \
		debug(M, ##__VA_ARGS__); \
		errno = 0;               \
		goto error;              \
	}

#endif
