include_directories(../include/)

add_library(myutil 
	utilities.c 
	../include/utilities.h
)

set_target_properties(myutil PROPERTIES PUBLIC_HEADER 
	dbg.h
	macros.h
	utilities.h
)