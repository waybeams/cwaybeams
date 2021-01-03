cmake_minimum_required(VERSION 3.10)

project(cwaybeams VERSION 1.0)

include_directories(include)

add_subdirectory(vendor/glfw)

configure_file(include/version.h.in include/version.h)

aux_source_directory(src CWAYBEAMS_SRCS)

add_executable(examples-glfw examples/glfw_main.c ${CWAYBEAMS_SRCS})
target_include_directories(examples-glfw PRIVATE vendor/gl/include)
target_include_directories(examples-glfw PRIVATE vendor/glfw/include)
target_link_libraries(examples-glfw glfw ${OPENGL_glu_LIBRARY} ${GLFW_LIBRARIES})

