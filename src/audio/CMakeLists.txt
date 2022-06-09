set(SRC
	mic.cpp
	speaker.cpp
	device.cpp
	)

set(INC
	mic.h
	speaker.h
	device.h
	)

set(LIBS
	OpenAL
	)

add_library(audio OBJECT "${SRC};${INC}")
target_include_directories(audio PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(audio "${LIBS}")
