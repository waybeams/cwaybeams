
message(STATUS "Building tests now")

set(TEST_SRCS
  dom_test.c
  layout_test.h
  layout_test.c
  test_helper.h
  test_helper.c
  )

set(TEST_HDRS
  minunit.h
  dom_test.h
  layout_test.h
  test_helper.h
  )

add_executable(cwaybeams-test test_main.c ${TEST_HDRS} ${TEST_SRCS})
target_link_libraries(cwaybeams-test cwaybeams)
target_include_directories(cwaybeams-test PUBLIC .)

