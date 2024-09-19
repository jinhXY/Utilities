cmake_minimum_required(VERSION 3.30.2)

project(my-utilities)

add_subdirectory(src)
add_subdirectory(test)

if(DEBUG_ENABLED)
	enable_testing()
	add_test(NAME test_util_print COMMAND test_util_print)
	# add_test(NAME test_util_cmp COMMAND test_util_cmp)
	# add_test(NAME test_util_to_string COMMAND test_util_to_string)
	# add_test(NAME test_util_from_string COMMAND test_util_from_string)
	# add_test(NAME test_util_misc COMMAND test_util_misc)
endif()