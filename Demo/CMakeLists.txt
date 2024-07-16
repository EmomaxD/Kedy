project(Demo)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SRC
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)

add_executable(Demo ${SRC})

# Include directories
target_include_directories(Demo PRIVATE 
    ${CMAKE_SOURCE_DIR}/Kedy/src
)

target_link_libraries(Demo PRIVATE Kedy)