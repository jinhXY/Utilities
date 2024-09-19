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
	E_SUCCESS,       /**< Successful execution */
	E_OUT_OF_MEMORY, /**< Ran out of memory */
	E_INVALID_ARG,   /**< Invalid arguments provided to the function */
	E_INVALID_OP     /**< Invalid operation / function call is not permitted */
} ErrStatus;

/**
 * @brief Obtains the name of the file, including the extension.
 */
#define THIS_FILENAME (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#ifndef CURRENT_FILE
	/**
	 * @brief Redefine this macro to modify the format of the file that gets printed out.
	 */
	#define CURRENT_FILE __FILE__
#endif

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
	#define debug(M, ...) fprintf(stderr, "DEBUG %s:%d: " M "\n", CURRENT_FILE, __LINE__, ##__VA_ARGS__)

	/**
	 * @brief Reimplementation of assert() that uses @ref CURRENT_FILE to customize the file name
	 * that is printed out.
	 */
	#define claim(expr)   ((expr) ? (void) 0 : __assert_fail(#expr, CURRENT_FILE, __LINE__, __func__))
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
	#define log_err(M, ...)  fprintf(stderr, "[ERROR] (%s:%d: errno: %s) " M "\n", CURRENT_FILE, __LINE__, clean_errno(), ##__VA_ARGS__)

	/**
	 * @brief Prints a warning message to `stderr`. Same format as printf.
	 */
	#define log_warn(M, ...) fprintf(stderr, "[WARN] (%s:%d: errno: %s) " M "\n", CURRENT_FILE, __LINE__, clean_errno(), ##__VA_ARGS__)

	/**
	 * @brief Prints an info message to `stderr`. Same format as printf.
	 */
	#define log_info(M, ...) fprintf(stderr, "[INFO] (%s:%d) " M "\n", CURRENT_FILE, __LINE__, ##__VA_ARGS__)
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
