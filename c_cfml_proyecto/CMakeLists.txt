cmake_minimum_required(VERSION 3.17)
project(c_cfml_proyecto C)

set(CMAKE_C_STANDARD 99)


add_executable(c_cfml_proyecto main.c)

find_package( SFML 2.5 COMPONENTS graphics  )
target_link_libraries(c_cfml_proyecto sfml-graphics)
target_link_libraries(c_cfml_proyecto csfml-graphics)