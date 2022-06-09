set(SRC
	server.cpp
	packet.cpp
	connection_manager.cpp
	connection.cpp
	client.cpp
	)

set(INC
	server.h
	packet.h
	connection_manager.h
	connection.h
	client.h
	)

set(LIBS
	asio
	)

add_library(net "${SRC};${INC}")
target_link_libraries(net "${LIBS}")