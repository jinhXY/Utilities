include_directories(
	../include
)

find_package(Check REQUIRED CONFIG)

set(TEST_LIBS
	baseutils
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
