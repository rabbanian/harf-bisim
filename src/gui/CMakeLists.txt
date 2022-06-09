set(SRC
	wrappers/qbackend.cpp
	)

set(INC
	wrappers/qbackend.h
	)

set(LIBS
	Qt5::Core
	)

set(RCS
	qml.qrc
	)

set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

add_library(gui OBJECT "${RCS};${SRC};${INC}")
target_link_libraries(gui "${LIBS}")

# should be removed when we don't need QML debuging or made PRIVATE so that it won't pollute other modules.
target_compile_definitions(gui PUBLIC $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
