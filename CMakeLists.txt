cmake_minimum_required(VERSION 3.13)

project(harf-bisim)
set(CMAKE_CXX_STANDARD 20)

include(cmake/prevent_in_source_builds.cmake)
#include(cmake/compiler_warnings.cmake)
include(cmake/external_packages.cmake)

option(WITH_CLIENT "build client application" ON)
option(WITH_SERVER "build server application" ON)

add_subdirectory(src)
add_subdirectory(external)
add_subdirectory(data)
