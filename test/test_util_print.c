#include "test_macros.h"
#include "utilities.h"

#include <check.h>
#include <float.h>
#include <limits.h>
#include <signal.h>
#include <stdlib.h>

#define test_print(msg, fn, ptr)     \
	printf(msg);                     \
	ck_assert(fn(stdout, ptr) >= 0); \
	printf("\n");

#define NUM_OF_FN 5

static const util_print_fn functions[NUM_OF_FN] = {
	util_generic_print,
	util_char_print,
	util_int_print,
	util_double_print,
	util_string_print
};

/* SECTION - Tests */

START_TEST(test_generic_print)
{
	int val       = 0;
	const void *p = &val;

	test_print("Generic pointer print: ", util_generic_print, p);
}

END_TEST

START_TEST(test_print_null)
{
	test_print("NULL print: ", functions[_i], NULL);
}

END_TEST

START_TEST(test_char_print)
{
	char c        = '?';
	const void *p = &c;

	test_print("Print char: ", util_char_print, p);
}

END_TEST

START_TEST(test_int_print)
{
	int n         = 10;
	const void *p = &n;

	test_print("Print integer: ", util_int_print, p);
}

END_TEST

START_TEST(test_int_print_min_max)
{
	int n = INT_MIN;
	test_print("Print min integer: ", util_int_print, &n);

	n = INT_MAX;
	test_print("Print max integer: ", util_int_print, &n);
}

END_TEST

START_TEST(test_double_print)
{
	double n      = 12345678912345678.9123456789123456789;
	const void *p = &n;

	test_print("Print double: ", util_double_print, p);
}

END_TEST

START_TEST(test_double_print_min_max)
{
	double n = -DBL_MAX;
	test_print("Print min negative double: ", util_double_print, &n);

	n = -DBL_MIN;
	test_print("Print max negative double: ", util_double_print, &n);

	n = DBL_MAX;
	test_print("Print max positive double: ", util_double_print, &n);

	n = DBL_MIN;
	test_print("Print min positive double: ", util_double_print, &n);
}

END_TEST

START_TEST(test_string_print)
{
	char *str = "This is a test";

	test_print("Print string: ", util_string_print, str);
}

END_TEST

#ifndef NDEBUG
START_TEST(test_invalid_arg)
{
	functions[_i](NULL, NULL);
}
#endif

END_TEST

/* !SECTION */

Suite *print_suite_create(void)
{
	Suite *s;
	TCase *core;
	TCase *edges;
	TCase *invalid_args;

	s = suite_create("Printing functions");

	core = tcase_create(CASE_CORE);
	tcase_add_test(core, test_generic_print);
	tcase_add_test(core, test_char_print);
	tcase_add_test(core, test_int_print);
	tcase_add_test(core, test_double_print);
	tcase_add_test(core, test_string_print);

	edges = tcase_create(CASE_LIMITS);
	tcase_add_loop_test(edges, test_print_null, 0, NUM_OF_FN);
	tcase_add_test(edges, test_print_null);
	tcase_add_test(edges, test_int_print_min_max);
	tcase_add_test(edges, test_double_print_min_max);

	invalid_args = tcase_create(CASE_INVALID);
#ifndef NDEBUG // This test relies on the behavior of asserts
	tcase_add_loop_test_raise_signal(invalid_args, test_invalid_arg, SIGABRT, 0, NUM_OF_FN);
#endif
	tcase_set_tags(invalid_args, NO_FORK_TAG);

	suite_add_tcase(s, core);
	suite_add_tcase(s, edges);
	suite_add_tcase(s, invalid_args);

	return s;
}

int main(void)
{
	MAIN_RUNNER(print_suite_create);
}
