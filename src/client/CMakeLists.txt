
set(SRC
	main.cpp
	)

set(INC
	)

set(LIBS
	Qt5::Widgets
	Qt5::Quick
	gui
	audio
	net
	)

add_executable(${PROJECT_NAME}-client "${SRC};${INC}")
target_link_libraries(${PROJECT_NAME}-client "${LIBS}")
install(TARGETS ${PROJECT_NAME}-client)
