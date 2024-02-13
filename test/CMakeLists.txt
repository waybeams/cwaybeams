cmake_minimum_required(VERSION 3.13)

set(UNIT_SOURCES
  "${CMAKE_CURRENT_SOURCE_DIR}/main_test.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/arena_test.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/beam_test.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/hash_test.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/minunit.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/node_test.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/node_visitor_test.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/test_helper.c"
  PARENT_SCOPE
  )

message(STATUS "UNIT_SOURCES defined")
message(STATUS "UNIT_SOURCES: ${UNIT_SOURCES}")

