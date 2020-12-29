cmake_minimum_required(VERSION 3.10)

project(cwaybeams VERSION 1.0)

include_directories(include)

add_subdirectory(vendor/glfw)

configure_file(include/version.h.in include/version.h)

aux_source_directory(src CWAYBEAMS_SRCS)

add_executable(glfw-example examples/main.c ${CWAYBEAMS_SRCS})
target_include_directories(glfw-example PRIVATE vendor/gl/include)
target_include_directories(glfw-example PRIVATE vendor/glfw/include)
target_link_libraries(glfw-example glfw ${OPENGL_glu_LIBRARY} ${GLFW_LIBRARIES})

