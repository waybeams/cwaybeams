
message(STATUS "Building tests now")

set(TEST_SRCS
  box_test.c
  fixtures/hfsm_keyboard.c
  hash_test.c
  hfsm_test.c
  layout_test.c
  node_test.c
  node_visitor_test.c
  test_helper.c
  )

set(TEST_HDRS
  box_test.h
  fixtures/hfsm_keyboard.h
  hash_test.h
  hfsm_test.h
  layout_test.h
  minunit.h
  node_test.h
  node_visitor_test.h
  test_helper.h
  )

add_executable(cwaybeams-test test_main.c ${TEST_HDRS} ${TEST_SRCS})
target_link_libraries(cwaybeams-test cwaybeams)
target_include_directories(cwaybeams-test PUBLIC .)

