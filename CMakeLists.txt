include(FindPkgConfig)
include(GNUInstallDirs)

#########################################
# Prepare primary library project
#########################################
message(STATUS "Configuring cwaybeams now")
cmake_minimum_required(VERSION 3.10)
project(cwaybeams LANGUAGES C VERSION 0.1)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR})
set(CMAKE_VERBOSE_MAKEFILE ON)
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# enable_testing()
configure_file(include/version.h.in include/version.h)
add_library(cwaybeams SHARED
	src/box.c
	src/layout.c
  src/hfsm.c
  src/node.c
  src/node_visitor.c
  vendor/hash/fast_hash.c
	)
target_include_directories(cwaybeams PUBLIC include src vendor/hash)
set_target_properties(cwaybeams PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(cwaybeams PROPERTIES SOVERSION 0)
target_include_directories(cwaybeams PRIVATE .)

#########################################
# Prepare test binary and examples
#########################################
add_subdirectory(test)
# add_subdirectory(examples/glfw)
