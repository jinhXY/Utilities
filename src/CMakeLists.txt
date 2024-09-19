include_directories(../include/)

set(LIB_SOURCES
	utilities.c
)

add_library(myutil STATIC ${LIB_SOURCES})

list(APPEND LIB_PUBLIC_HEADERS
	../include/dbg.h
	../include/macros.h
	../include/utilities.h
)

if (USE_CHECK)
	list(APPEND LIB_PUBLIC_HEADERS
		../include/test_macros.h
	)
endif()

set_target_properties(myutil PROPERTIES
	PUBLIC_HEADER "${LIB_PUBLIC_HEADERS}"
)

install(TARGETS myutil
	LIBRARY DESTINATION lib
	PUBLIC_HEADER DESTINATION include/${PROJECT_NAME})
