/**
 * @brief Contains useful macros for unit-testing with Check.
 *
 * @file test_macros.h
 */

#ifndef TEST_MACROS_H
#define TEST_MACROS_H

#include <check.h>
#include <stdlib.h>

/**
 * @brief Tag for tests that should not run when fork is enabled.
 */
#define NO_FORK_TAG "nofork"

/**
 * @brief Boilerplate for the main function.
 *
 * @param suite_fn Pointer to a function of type `Suite *(suite_fn)(void)`.
 */
#define MAIN_RUNNER(suite_fn)                                             \
	int number_failed;                                                    \
	Suite *s;                                                             \
	SRunner *sr;                                                          \
                                                                          \
	s  = suite_fn();                                                      \
	sr = srunner_create(s);                                               \
                                                                          \
	if (srunner_fork_status(sr) == CK_FORK) {                             \
		srunner_run_all(sr, CK_NORMAL);                                   \
	} else {                                                              \
		srunner_run_tagged(sr, NULL, NULL, NULL, NO_FORK_TAG, CK_NORMAL); \
	}                                                                     \
                                                                          \
	number_failed = srunner_ntests_failed(sr);                            \
	srunner_free(sr);                                                     \
                                                                          \
	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;


#endif
