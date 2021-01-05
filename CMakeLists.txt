include(FindPkgConfig)
include(GNUInstallDirs)


#########################################
# Prepare primary library project
#########################################
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
  src/dom_visitor.c
  src/hfsm.c
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


#########################################
# Prepare GTK+3 shared library
#########################################
find_package(GTK REQUIRED "gtk+-3.0")
pkg_check_modules(GTK REQUIRED "gtk+-3.0")

add_library(cwaybeams-gtk SHARED src/gtk/app.c)
set_target_properties(cwaybeams-gtk PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(cwaybeams-gtk PROPERTIES SOVERSION 0)
target_include_directories(cwaybeams-gtk PRIVATE ${GTK_INCLUDE_DIRS})
target_link_libraries(cwaybeams-gtk
  cwaybeams
  ${GTK}
  ${GTK_LIBRARIES}
  )

add_definitions(${GTK_CFLAGS_OTHER})
# add_definitions(${GTK3_CFLAGS_OTHER})
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -rdynamic")
# link_directories(${GTK3_LIBRARY_DIRS})


#########################################
# Prepare test binary and examples
#########################################
add_subdirectory(test)
add_subdirectory(examples/gtk)
# add_subdirectory(examples/glfw)

