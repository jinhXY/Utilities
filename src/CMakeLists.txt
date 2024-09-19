include_directories(../include/)

set(LIB_SOURCES
	utilities.c
)

add_library(myutil STATIC ${LIB_SOURCES})

set_target_properties(myutil PROPERTIES
	PUBLIC_HEADER dbg.h
	PUBLIC_HEADER macros.h
	PUBLIC_HEADER utilities.h
)

if (USE_CHECK)
	set_target_properties(myutil PROPERTIES
		PUBLIC_HEADER test_macros.h
	)
endif()

install(TARGETS myutil
	LIBRARY DESTINATION lib/$(PROJECT_NAME)
	PUBLIC_HEADER DESTINATION include/$(PROJECT_NAME))
