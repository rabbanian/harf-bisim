
set(SRC
	main.cpp
	)

set(INC
	)

set(LIBS
	net
	)

add_executable(${PROJECT_NAME}-server "${SRC};${INC}")
target_link_libraries(${PROJECT_NAME}-server "${LIBS}")
install(TARGETS ${PROJECT_NAME}-server)
