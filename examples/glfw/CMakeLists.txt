
message(STATUS "Building ./bin/examples/glfw now")
add_executable(examples-glfw glfw_main.c)

target_link_libraries(examples-glfw glfw
  cwaybeams
  ${OPENGL_glu_LIBRARY}
  ${GLFW_LIBRARIES}
  )

