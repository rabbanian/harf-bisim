add_subdirectory(openal-soft)

add_library(asio INTERFACE)
target_include_directories(asio INTERFACE asio/asio/include)
