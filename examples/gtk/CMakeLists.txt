# Configure the GTK+ application
# To get dependencies (for now):
# sudo apt install gnome-devel
# A nice looking cmake sample file to come back to:
# https://codereview.stackexchange.com/questions/235892/gtk-cmake-setup

find_package(GTK REQUIRED "gtk+-3.0")
pkg_check_modules(GTK REQUIRED "gtk+-3.0")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -rdynamic")
add_definitions(${GTK3_CFLAGS_OTHER})
link_directories(${GTK3_LIBRARY_DIRS})

add_executable(examples-gtk examples/gtk_main.c ${CWAYBEAMS_SRCS})
target_include_directories(examples-gtk PRIVATE ${GTK_INCLUDE_DIRS})
target_link_libraries(examples-gtk ${GTK} ${GTK3_LIBRARIES} ${GTK3_LIBRARY_DIRS})
