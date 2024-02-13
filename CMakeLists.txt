include(FindPkgConfig)
include(GNUInstallDirs)

#########################################
# Prepare primary library project
#########################################
message(STATUS "Configuring cwaybeams now")
cmake_minimum_required(VERSION 3.10)
project(cwaybeams LANGUAGES C VERSION 0.1)

configure_file(include/version.h.in include/version.h)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(OpenGL_GL_PREFERENCE GLVND)

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)

find_package(sdl2 REQUIRED)

if (MSVC)
  add_compile_options(/W3 /WX)
else()
  add_compile_options(-W -Wall -Werror)
endif()

set(TODO_EXAMPLE_SOURCES
  "${CMAKE_CURRENT_SOURCE_DIR}/examples/todo/main_todo.c"
  )

set(FAST_HASH_SOURCES
  "${CMAKE_CURRENT_SOURCE_DIR}/vendor/hash/fast_hash.c"
  )

# set(SDL_STATIC ON CACHE BOOL "" FORCE)
# set(SDL_SHARED OFF CACHE BOOL "" FORCE)
# add_subdirectory(vendor/sdl3)

add_subdirectory(src)

# Shared library build
add_library(cwaybeams SHARED
  ${BEAM_SOURCES}
  ${SDL_RENDERER_SOURCES}
  # ${GLFW_RENDERER_SOURCES}
  ${FAST_HASH_SOURCES}
  )

# if(TARGET SDL2)
#   target_compile_options(SDL2 PRIVATE
#     $<$<OR:$<C_COMPILER_ID:GNU>,$<C_COMPILER_ID:Clang>>:
#     -Wno-unused-parameter
#     -Wno-sign-compare>
#     )
# endif()

target_link_libraries(cwaybeams SDL2 SDL2main)

set_target_properties(cwaybeams PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(cwaybeams PROPERTIES SOVERSION 0)

target_include_directories(cwaybeams PUBLIC include)
target_include_directories(cwaybeams PRIVATE
  src
  vendor/hash
  )

# target_link_libraries(cwaybeams glfw)
# target_link_libraries(cwaybeams OpenGL::GL)

add_subdirectory(test)

# Test executable
add_executable(cwaybeams-test
  ${UNIT_SOURCES}
  ${BEAM_SOURCES}
  # ${SDL_RENDERER_SOURCES}
  # ${GLFW_RENDERER_SOURCES}
  )

target_compile_definitions(cwaybeams-test PRIVATE TEST_MODE=1)

target_include_directories(cwaybeams-test PRIVATE
  include
  src
  test
  vendor/hash
  )

# target_link_libraries(cwaybeams-test glfw)
# target_link_libraries(cwaybeams-test OpenGL::GL)

# Example executable
add_executable(todo-example
  ${TODO_EXAMPLE_SOURCES}
  ${BEAM_SOURCES}
  ${SDL_RENDERER_SOURCES}
  )

target_link_libraries(todo-example SDL2 SDL2main)

target_include_directories(todo-example PRIVATE
  examples/todo
  include
  src
  vendor/hash
  )

# target_link_libraries(todo-example glfw)
# target_link_libraries(todo-example OpenGL::GL)
