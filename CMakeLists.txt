include(FindPkgConfig)
include(GNUInstallDirs)

message(STATUS "Configuring cwaybeams now")
cmake_minimum_required(VERSION 3.10)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR})
set(CMAKE_VERBOSE_MAKEFILE ON)
project(cwaybeams VERSION 0.1)
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# enable_testing()
configure_file(include/version.h.in include/version.h)

add_library(cwaybeams SHARED
	src/dom.c
	src/layout.c
	)

target_include_directories(cwaybeams PUBLIC include src)

set_target_properties(cwaybeams PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(cwaybeams PROPERTIES SOVERSION 0)
target_include_directories(cwaybeams PRIVATE .)

# TODO(lbayes): Investigate library installation options.
# Blob found here:
# https://stackoverflow.com/questions/17511496/how-to-create-a-shared-library-with-cmake
# install(TARGETS cwaybeams
# LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
# PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
# )

# Add example project executables
add_subdirectory(test)
add_subdirectory(examples/glfw)
add_subdirectory(examples/gtk)

