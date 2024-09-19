#include "test_macros.h"
#include "utilities.h"

#include <limits.h>

#define test_equal(fn, x, y)  \
	ck_assert(fn(x, y) == 0); \
	ck_assert(fn(y, x) == 0);

#define test_diff(fn, x, y)  \
	ck_assert(fn(x, y) < 0); \
	ck_assert(fn(y, x) > 0);

#define test_null(fn, x) /* x cannot be NULL */ \
	ck_assert(fn(NULL, x) < 0);                 \
	ck_assert(fn(x, NULL) > 0);                 \
	ck_assert(fn(NULL, NULL) == 0);

/* SECTION - Tests */

START_TEST(test_char_cmp_equal)
{
	char c1 = 'a';
	char c2 = 'a';

	test_equal(util_char_cmp, &c1, &c2);
}

END_TEST

START_TEST(test_char_cmp_diff)
{
	char c1 = 'X';
	char c2 = 'Y';

	test_diff(util_char_cmp, &c1, &c2);
}

END_TEST

START_TEST(test_char_cmp_null)
{
	char c = '4';

	test_null(util_char_cmp, &c);
}

END_TEST

START_TEST(test_char_limits)
{
	char c1 = CHAR_MIN;
	char c2 = CHAR_MAX;

	test_diff(util_char_cmp, &c1, &c2);
}

START_TEST(test_int_cmp_equal)
{
	int i1 = 40381;
	int i2 = 40381;

	test_equal(util_int_cmp, &i1, &i2);
}

END_TEST

START_TEST(test_int_cmp_diff)
{
	int i1 = 30;
	int i2 = 90;

	test_diff(util_int_cmp, &i1, &i2);
}

END_TEST

START_TEST(test_int_cmp_null)
{
	int i = 0;

	test_null(util_int_cmp, &i);
}

END_TEST

START_TEST(test_int_cmp_limits)
{
	int i1 = INT_MIN;
	int i2 = INT_MAX;

	test_diff(util_int_cmp, &i1, &i2);
}

END_TEST

START_TEST(test_double_cmp_equal)
{
	double d1 = 123456789012.34567890;
	double d2 = 123456789012.34567890;

	test_equal(util_double_cmp, &d1, &d2);
}

END_TEST

START_TEST(test_double_cmp_diff)
{
	double d1 = 12.345678901234567890;
	double d2 = 987654321.987654321;

	test_diff(util_double_cmp, &d1, &d2);
}

END_TEST

START_TEST(test_double_cmp_null)
{
	double d = DBL_EPSILON;

	test_null(util_double_cmp, &d);
}

END_TEST

START_TEST(test_double_cmp_limits)
{
	double d1 = -DBL_MAX;
	double d2 = DBL_MAX;

	test_diff(util_double_cmp, &d1, &d2);
}

END_TEST

START_TEST(test_double_cmp_limits2)
{
	double d1 = DBL_MIN;
	double d2 = DBL_MAX;

	test_diff(util_double_cmp, &d1, &d2);
}

END_TEST

START_TEST(test_string_cmp_equal)
{
	const char *s1 = "abcdef";
	const char *s2 = "abcdef";

	test_equal(util_string_cmp, s1, s2);
}

END_TEST

START_TEST(test_string_cmp_diff)
{
	const char *s1 = "aaa";
	const char *s2 = "aab";

	test_diff(util_string_cmp, s1, s2);
}

END_TEST

START_TEST(test_string_cmp_null)
{
	const char *s = "null";

	test_null(util_string_cmp, s);
}

END_TEST

START_TEST(test_string_cmp_limits)
{
	const char *s1 = "";
	const char *s2 = "1";

	test_diff(util_string_cmp, s1, s2);
}

/* !SECTION */

Suite *cmp_suite_create(void)
{
	Suite *s;
	TCase *core;
	TCase *limits;

	s = suite_create("Comparison functions");

	core = tcase_create(CASE_CORE);
	tcase_add_test(core, test_char_cmp_equal);
	tcase_add_test(core, test_char_cmp_diff);
	tcase_add_test(core, test_int_cmp_equal);
	tcase_add_test(core, test_int_cmp_diff);
	tcase_add_test(core, test_double_cmp_equal);
	tcase_add_test(core, test_double_cmp_diff);
	tcase_add_test(core, test_string_cmp_equal);
	tcase_add_test(core, test_string_cmp_diff);

	limits = tcase_create(CASE_LIMITS);
	tcase_add_test(limits, test_char_cmp_null);
	tcase_add_test(limits, test_char_limits);
	tcase_add_test(limits, test_int_cmp_null);
	tcase_add_test(limits, test_int_cmp_limits);
	tcase_add_test(limits, test_double_cmp_null);
	tcase_add_test(limits, test_double_cmp_limits);
	tcase_add_test(limits, test_double_cmp_limits2);
	tcase_add_test(limits, test_string_cmp_null);
	tcase_add_test(limits, test_string_cmp_limits);

	suite_add_tcase(s, core);
	suite_add_tcase(s, limits);

	return s;
}

int main(void)
{
	MAIN_RUNNER(cmp_suite_create)
}
