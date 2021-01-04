# Configure the GTK+ application
# To get dependencies (for now):
# sudo apt install gnome-devel
# A nice looking cmake sample file to come back to:
# https://codereview.stackexchange.com/questions/235892/gtk-cmake-setup

add_executable(examples-gtk gtk_main.c)

target_link_libraries(examples-gtk cwaybeams-gtk)

