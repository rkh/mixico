require 'mkmf'

dir_config("mixico")
have_library("c", "main")

create_makefile("mixico")
