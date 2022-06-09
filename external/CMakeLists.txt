option(ALSOFT_UTILS "Build utility programs"  OFF)
option(ALSOFT_EXAMPLES  "Build example programs"  OFF)
set(LIBTYPE "STATIC" CACHE STRING "OpenAL build type" FORCE)

add_subdirectory(openal-soft EXCLUDE_FROM_ALL)

add_library(asio INTERFACE)
target_include_directories(asio INTERFACE asio/asio/include)
