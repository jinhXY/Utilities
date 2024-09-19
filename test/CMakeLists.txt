include_directories(
	../include
)

find_package(Check REQUIRED CONFIG)

# set(TEST_LIST
# 	test_util_print.c
# 	test_util_cmp.c
# 	test_util_to_string.c
# 	test_util_from_string.c
# 	test_util_misc.c
# )

set(TEST_LIBS
	myutil
	check
)

add_executable(test_util_print test_util_print.c)
target_link_libraries(test_util_print ${TEST_LIBS})

add_executable(test_util_cmp test_util_cmp.c)
target_link_libraries(test_util_cmp ${TEST_LIBS})

add_executable(test_util_to_string test_util_to_string.c)
target_link_libraries(test_util_to_string ${TEST_LIBS})

add_executable(test_util_from_string test_util_from_string.c)
target_link_libraries(test_util_from_string ${TEST_LIBS})

# add_executable(test_util_misc test_util_misc.c)
# target_link_libraries(test_util_misc ${TEST_LIBS})

