
set(SRC
	main.cpp
	)

set(INC
	)

set(LIBS
	net
	)

add_executable(${PROJECT_NAME}_server "${SRC};${INC}")
target_link_libraries(${PROJECT_NAME}_server "${LIBS}")
