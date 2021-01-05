
message(STATUS "Building tests now")

set(TEST_SRCS
  dom_test.c
  dom_visitor_test.c
  fixtures/hfsm_keyboard.c
  hfsm_test.c
  layout_test.c
  test_helper.c
  )

set(TEST_HDRS
  minunit.h
  dom_test.h
  dom_visitor_test.h
  fixtures/hfsm_keyboard.h
  hfsm_test.h
  layout_test.h
  test_helper.h
  )

add_executable(cwaybeams-test test_main.c ${TEST_HDRS} ${TEST_SRCS})
target_link_libraries(cwaybeams-test cwaybeams)
target_include_directories(cwaybeams-test PUBLIC .)

