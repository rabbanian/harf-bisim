include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(net)
add_subdirectory(gui)
add_subdirectory(audio)

if (WITH_CLIENT)
  add_subdirectory(client)
endif()

if (WITH_SERVER)
  add_subdirectory(server)
endif()
