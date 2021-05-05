include(FindPkgConfig)
include(GNUInstallDirs)

#########################################
# Prepare primary library project
#########################################
message(STATUS "Configuring cwaybeams now")
cmake_minimum_required(VERSION 3.10)
project(cwaybeams LANGUAGES C VERSION 0.1)

configure_file(include/version.h.in include/version.h)

include_directories(include)
include_directories(src)
include_directories(test)
include_directories(vendor/hash)

set(AppSources
	src/beam.c
	src/hfsm.c
	src/node.c
	src/node_visitor.c
	vendor/hash/fast_hash.c
	)

set(AppHeaders
	include/beam.h
	include/debug.h
	include/hfsm.h
	include/log.h
	include/node.h
	include/node_visitor.h
	include/render.h
	include/version.h
	vendor/hash/fast_hash.h
	)

set(TestSources
	test/beam_test.c
	test/beam_test.h
	test/hash_test.c
	test/hash_test.h
	test/hfsm_test.c
	test/hfsm_test.h
	test/minunit.h
	test/node_test.c
	test/node_test.h
	test/node_visitor_test.c
	test/node_visitor_test.h
	test/test_helper.c
	test/test_helper.h
	test/fixtures/hfsm_keyboard.c
	test/fixtures/hfsm_keyboard.h
	)

add_library(cwaybeams SHARED
	${AppSources}
	${AppHeaders}
	)

set_target_properties(cwaybeams PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(cwaybeams PROPERTIES SOVERSION 0)

add_executable(cwaybeams-test test/main_test.c
	${AppSources}
	${AppHeaders}
	${TestSources}
	)

target_compile_definitions(cwaybeams-test PRIVATE TEST_MODE=1)
