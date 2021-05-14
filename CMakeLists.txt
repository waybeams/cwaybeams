include(FindPkgConfig)
include(GNUInstallDirs)

#########################################
# Prepare primary library project
#########################################
message(STATUS "Configuring cwaybeams now")
cmake_minimum_required(VERSION 3.10)
project(cwaybeams LANGUAGES C VERSION 0.1)

configure_file(include/version.h.in include/version.h)

set(OpenGL_GL_PREFERENCE GLVND)

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)

if (MSVC)
    add_compile_options(/W3 /WX)
else()
	add_compile_options(-W -Wall -Werror)
endif()

set(AppSources
		src/beam.c
		src/node.c
		src/node_visitor.c
		src/render/glfw.c
		vendor/hash/fast_hash.c
		)

set(AppHeaders
		include/beam.h
		include/log.h
		include/node.h
		include/node_visitor.h
		include/render.h
		include/version.h
		vendor/hash/fast_hash.h
		src/render/glfw.h include/shared.h)

set(TestSources
		test/beam_test.c
		test/beam_test.h
		test/hash_test.c
		test/hash_test.h
		test/minunit.h
		test/node_test.c
		test/node_test.h
		test/node_visitor_test.c
		test/node_visitor_test.h
		test/test_helper.c
		test/test_helper.h
		)

# Shared library build
add_library(cwaybeams SHARED
		${AppSources}
		${AppHeaders}
		)

set_target_properties(cwaybeams PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(cwaybeams PROPERTIES SOVERSION 0)

target_include_directories(cwaybeams PUBLIC include)
target_include_directories(cwaybeams PRIVATE src)
target_include_directories(cwaybeams PRIVATE vendor/hash)
target_link_libraries(cwaybeams glfw)
target_link_libraries(cwaybeams OpenGL::GL)

# Test executable
add_executable(cwaybeams-test test/main_test.c
		${AppSources}
		${AppHeaders}
		${TestSources}
		)

target_compile_definitions(cwaybeams-test PRIVATE TEST_MODE=1)
target_include_directories(cwaybeams-test PRIVATE include)
target_include_directories(cwaybeams-test PRIVATE src)
target_include_directories(cwaybeams-test PRIVATE test)
target_include_directories(cwaybeams-test PRIVATE vendor/hash)
target_link_libraries(cwaybeams-test glfw)
target_link_libraries(cwaybeams-test OpenGL::GL)

# Example executable
add_executable(todo-example examples/todo/main_todo.c
		${AppSources}
		${AppHeaders}
		)

target_include_directories(todo-example PUBLIC include)
target_include_directories(todo-example PRIVATE src)
target_include_directories(todo-example PRIVATE vendor/hash)
target_link_libraries(todo-example glfw)
target_link_libraries(todo-example OpenGL::GL)
