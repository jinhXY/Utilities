cmake_minimum_required(VERSION 3.30.2)

project(my-utilities)

add_subdirectory(src)

install(TARGETS myutil LIBRARY DESTINATION lib
		PUBLIC_HEADER DESTINATION include/$(PROJECT_NAME))