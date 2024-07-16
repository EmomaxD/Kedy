cmake_minimum_required(VERSION 3.10)
project(root)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(Kedy)
add_subdirectory(Demo)
#add_subdirectory(Editor)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Demo)