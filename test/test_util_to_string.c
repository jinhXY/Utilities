#include "macros.h"
#include "test_macros.h"
#include "utilities.h"

#include <inttypes.h>
#include <limits.h>

#define NUM_OF_FN 5

#define test_to_string(fn, x, msg, str)                      \
	char *ptr = fn(x);                                       \
	printf("%s: %s\n", msg, DEF_IF_NULL(ptr));               \
	printf("Expected string: %s (%zu)\n", str, strlen(str)); \
	if (ptr) {                                               \
		ck_assert_str_eq(ptr, str);                          \
		free(ptr);                                           \
	}


static const util_to_string_fn functions[] = {
	util_generic_to_string,
	util_char_to_string,
	util_int_to_string,
	util_double_to_string,
	util_string_to_string
};

/* SECTION - Tests */

START_TEST(test_generic_to_string)
{
	long x = 0;
	char str[128];
	snprintf(str, 128, "0x%" PRIxPTR, (uintptr_t) &x);

	test_to_string(util_generic_to_string, &x, "Generic pointer", str);
}

END_TEST

START_TEST(test_char_to_string)
{
	char c = '!';

	test_to_string(util_char_to_string, &c, "Char", "!");
}

END_TEST

START_TEST(test_int_to_string)
{
	int i = 0;

	test_to_string(util_int_to_string, &i, "Integer", "0");
}

END_TEST

START_TEST(test_double_to_string)
{
	double d = 1234567.8901234567890;
	char str[128];
	snprintf(str, 128, "%.*g", DBL_DIG, d);

	test_to_string(util_double_to_string, &d, "Double", str);
}

END_TEST

START_TEST(test_string_to_string)
{
	char *str = "Bananas";

	test_to_string(util_string_to_string, str, "String", str);
}

END_TEST

START_TEST(test_null_to_string)
{
	ck_assert(functions[_i](NULL) == NULL);
}

END_TEST

START_TEST(test_char_to_string_nul)
{
	char c = '\0';

	test_to_string(util_char_to_string, &c, "NUL character", "");
}

START_TEST(test_int_to_string_max)
{
	int i1 = INT_MAX;
	char str1[128];
	snprintf(str1, 128, "%d", i1);

	test_to_string(util_int_to_string, &i1, "Max integer", str1);
}

END_TEST

START_TEST(test_int_to_string_min)
{
	int i2 = INT_MIN;
	char str2[128];
	snprintf(str2, 128, "%d", i2);

	test_to_string(util_int_to_string, &i2, "Min integer", str2);
}

END_TEST

START_TEST(test_double_to_string_max)
{
	double d = -DBL_MAX;
	char str[128];
	snprintf(str, 128, "%.*g", DBL_DIG, d);

	test_to_string(util_double_to_string, &d, "Double max", str);
}

END_TEST

START_TEST(test_double_to_string_min)
{
	double d = -DBL_MIN;
	char str[128];
	snprintf(str, 128, "%.*g", DBL_DIG, d);

	test_to_string(util_double_to_string, &d, "Double min", str);
}

END_TEST

START_TEST(test_string_to_string_empty)
{
	char *str = "";

	test_to_string(util_string_to_string, str, "Empty string", str);
}

END_TEST

/* !SECTION */

Suite *to_string_suite_create(void)
{
	Suite *s;
	TCase *core;
	TCase *limits;

	s = suite_create("To string functions");

	core = tcase_create(CASE_CORE);
	tcase_add_test(core, test_generic_to_string);
	tcase_add_test(core, test_char_to_string);
	tcase_add_test(core, test_int_to_string);
	tcase_add_test(core, test_double_to_string);
	tcase_add_test(core, test_string_to_string);
	tcase_add_loop_test(core, test_null_to_string, 0, NUM_OF_FN);

	limits = tcase_create(CASE_LIMITS);
	tcase_add_test(limits, test_char_to_string_nul);
	tcase_add_test(limits, test_int_to_string_max);
	tcase_add_test(limits, test_int_to_string_min);
	tcase_add_test(limits, test_double_to_string_max);
	tcase_add_test(limits, test_double_to_string_min);
	tcase_add_test(limits, test_string_to_string_empty);

	suite_add_tcase(s, core);
	suite_add_tcase(s, limits);

	return s;
}

int main(void)
{
	// Temp code to check that macros are properly set
	// printf("Pointer: %d\n", (2 + (int) ceil(log2((double) UINTPTR_MAX) / 4)));
	// printf("Double: %d\n", (1 + DBL_DIG + 1 + 2 + (int) ceil(log10(DBL_MAX_10_EXP))));
	// printf("Long: %d\n", (1 + (int) ceil(log10((double) LONG_MAX))));
	// printf("Int: %d\n", (1 + (int) ceil(log10(INT_MAX))));

	MAIN_RUNNER(to_string_suite_create);
}
