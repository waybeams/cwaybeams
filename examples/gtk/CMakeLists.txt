# Configure the GTK+ application
# To get dependencies (for now):
# sudo apt install gnome-devel
# A nice looking cmake sample file to come back to:
# https://codereview.stackexchange.com/questions/235892/gtk-cmake-setup

message(STATUS "Building ./bin/examples/gtk now")
add_executable(examples-gtk gtk_main.c)

find_package(GTK REQUIRED "gtk+-3.0")
pkg_check_modules(GTK REQUIRED "gtk+-3.0")

target_link_libraries(examples-gtk
  cwaybeams
  ${GTK}
  ${GTK_LIBRARIES}
  )

target_include_directories(examples-gtk PRIVATE
  ${GTK_INCLUDE_DIRS}
  )

add_definitions(${GTK_CFLAGS_OTHER})
# add_definitions(${GTK3_CFLAGS_OTHER})
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -rdynamic")
# link_directories(${GTK3_LIBRARY_DIRS})

