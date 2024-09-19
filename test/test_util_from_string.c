#include "test_macros.h"
#include "utilities.h"

#include <limits.h>
#include <signal.h>

#define test_from_string(ptr, str, fn, test) \
	ptr = fn(str);                           \
	ck_assert(test);                         \
	free(ptr);

#define NUM_OF_FN 4

static const util_elem_from_string_fn functions[] = {
	util_char_from_string,
	util_int_from_string,
	util_double_from_string,
	util_string_from_string
};

/* SECTION - Tests */

START_TEST(test_char_from_string)
{
	const char *str = "c";
	char *p;

	test_from_string(p, str, util_char_from_string, *p == 'c');
}

END_TEST

START_TEST(test_int_from_string)
{
	const char *str = "12345";
	int *p;

	test_from_string(p, str, util_int_from_string, *p == 12345);
}

END_TEST

START_TEST(test_double_from_string)
{
	const char *str = "123456789009.87654321";
	double *p;

	test_from_string(p, str, util_double_from_string, *p == 123456789009.87654321);
}

END_TEST

START_TEST(test_string_from_string)
{
	const char *str = "World Hello";
	char *p;

	test_from_string(p, str, util_string_from_string, strcmp(str, p) == 0);
}

END_TEST

START_TEST(test_char_from_string_nul)
{
	const char *str = "";
	char *p;

	test_from_string(p, str, util_char_from_string, *p == '\0');
}

END_TEST

START_TEST(test_char_from_string_trailing)
{
	const char *str = "cdefghijk0987654321";
	char *p;

	test_from_string(p, str, util_char_from_string, *p == 'c');
}

END_TEST

START_TEST(test_int_from_string_trailing)
{
	const char *str = "12345qwerty";
	int *p;

	test_from_string(p, str, util_int_from_string, *p == 12345);
}

END_TEST

START_TEST(test_int_from_string_middle)
{
	const char *str = "123qwerty45";
	int *p;

	test_from_string(p, str, util_int_from_string, *p == 123);
}

END_TEST

START_TEST(test_int_from_string_leading)
{
	const char *str = "qwerty12345";
	int *p;

	test_from_string(p, str, util_int_from_string, p == NULL);
}

END_TEST

START_TEST(test_int_from_string_overflow)
{
	char str[128];
	int *p;

	snprintf(str, 128, "%u", (unsigned) INT_MAX + 1);
	test_from_string(p, str, util_int_from_string, p == NULL);
}

END_TEST

START_TEST(test_int_from_string_underflow)
{
	char str[128];
	int *p;

	snprintf(str + 1, 127, "%u", (unsigned) INT_MIN + 1);
	str[0] = '-'; // Add minus sign
	test_from_string(p, str, util_int_from_string, p == NULL);
}

END_TEST

START_TEST(test_int_from_string_invalid)
{
	const char *str = "cfpqwo i1388";
	int *p;

	test_from_string(p, str, util_int_from_string, p == NULL);
}

END_TEST

START_TEST(test_int_from_string_empty)
{
	const char *str = "";
	int *p;

	test_from_string(p, str, util_int_from_string, p == NULL);
}

END_TEST

START_TEST(test_double_from_string_trailing)
{
	const char *str = "1234.567nbvcxz";
	double *p;

	test_from_string(p, str, util_double_from_string, *p == 1234.567);
}

END_TEST

START_TEST(test_double_from_string_middle)
{
	const char *str = "-123.4nbvcxz09.87654321";
	double *p;

	test_from_string(p, str, util_double_from_string, *p == -123.4);
}

END_TEST

START_TEST(test_double_from_string_leading)
{
	const char *str = "nbvcxz1234.87654321";
	double *p;

	test_from_string(p, str, util_double_from_string, p == NULL);
}

END_TEST

START_TEST(test_double_from_string_overflow)
{
	const char *str = "34e+1024";
	double *p;

	test_from_string(p, str, util_double_from_string, p == NULL);
}

END_TEST

START_TEST(test_double_from_string_underflow)
{
	const char *str = "34e-1024";
	double *p;

	test_from_string(p, str, util_double_from_string, p == NULL);
}

END_TEST

START_TEST(test_double_from_string_exp)
{
	const char *str = "1e-3";
	double *p;

	test_from_string(p, str, util_double_from_string, *p == 0.001);
}

END_TEST

START_TEST(test_double_from_string_hex)
{
	const char *str = "0x1F6db9";
	double *p;

	test_from_string(p, str, util_double_from_string, *p == 2059705);
}

END_TEST

START_TEST(test_double_from_string_hex_exp)
{
	const char *str = "0x1Fp-19";
	double *p;

	test_from_string(p, str, util_double_from_string, *p - 5.91278076172e-05 <= DBL_EPSILON);
}

END_TEST

START_TEST(test_double_from_string_hex_neg)
{
	/* NOTE Not sure if strtod() is supposed to accept this, might be implementation defined */
	const char *str = "-0x1F";
	double *p;

	test_from_string(p, str, util_double_from_string, *p == -31);
}

END_TEST

START_TEST(test_double_from_string_inf)
{
	const char *str = "INF";
	double *p;

	test_from_string(p, str, util_double_from_string, !isfinite(*p));
}

END_TEST

START_TEST(test_double_from_string_nan)
{
	const char *str = "NAN";
	double *p;

	test_from_string(p, str, util_double_from_string, isnan(*p));
}

END_TEST

START_TEST(test_double_from_string_empty)
{
	const char *str = "";
	double *p;

	test_from_string(p, str, util_double_from_string, p == NULL);
}

END_TEST

START_TEST(test_string_from_string_empty)
{
	const char *str = "";
	char *p;

	test_from_string(p, str, util_string_from_string, strcmp(str, p) == 0);
}

END_TEST

START_TEST(test_from_null_string)
{
	/* Should either segfault or fail an assertion */
	void *p;

	test_from_string(p, NULL, functions[_i], 0);
}

END_TEST

/* !SECTION */

Suite *from_string_suite_create(void)
{
	Suite *s;
	TCase *core;
	TCase *limits;
	TCase *invalid;
	TCase *signal_invalid;

	s = suite_create("From string functions");

	core = tcase_create(CASE_CORE);
	tcase_add_test(core, test_char_from_string);
	tcase_add_test(core, test_int_from_string);
	tcase_add_test(core, test_double_from_string);
	tcase_add_test(core, test_string_from_string);

	limits = tcase_create(CASE_LIMITS);
	tcase_add_test(limits, test_char_from_string_nul);
	tcase_add_test(limits, test_char_from_string_trailing);
	tcase_add_test(limits, test_int_from_string_trailing);
	tcase_add_test(limits, test_int_from_string_middle);
	tcase_add_test(limits, test_int_from_string_empty);
	tcase_add_test(limits, test_double_from_string_trailing);
	tcase_add_test(limits, test_double_from_string_middle);
	tcase_add_test(limits, test_double_from_string_exp);
	tcase_add_test(limits, test_double_from_string_hex);
	tcase_add_test(limits, test_double_from_string_hex_exp);
	tcase_add_test(limits, test_double_from_string_inf);
	tcase_add_test(limits, test_double_from_string_nan);
	tcase_add_test(limits, test_double_from_string_empty);
	tcase_add_test(limits, test_string_from_string_empty);

	invalid = tcase_create(CASE_INVALID);
	tcase_add_test(invalid, test_int_from_string_leading);
	tcase_add_test(invalid, test_int_from_string_overflow);
	tcase_add_test(invalid, test_int_from_string_underflow);
	tcase_add_test(invalid, test_int_from_string_invalid);
	tcase_add_test(invalid, test_double_from_string_leading);
	tcase_add_test(invalid, test_double_from_string_overflow);
	tcase_add_test(invalid, test_double_from_string_underflow);
	tcase_add_test(invalid, test_double_from_string_hex_neg);

	signal_invalid = tcase_create(CASE_SIGNAL_INVALID);
	tcase_add_loop_test_raise_signal(signal_invalid, test_from_null_string, SIGABRT, 0, NUM_OF_FN);
	tcase_set_tags(signal_invalid, NO_FORK_TAG);

	suite_add_tcase(s, core);
	suite_add_tcase(s, limits);
	suite_add_tcase(s, invalid);
	suite_add_tcase(s, signal_invalid);

	return s;
}

int main(void)
{
	MAIN_RUNNER(from_string_suite_create);
}
