
cmake_minimum_required(VERSION 3.18.1)
project(myProject VERSION 1.0)
file(GLOB_RECURSE SRC_FILE src/*.c)
add_executable(main test/main.c ${SRC_FILE})
target_include_directories(main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc/)
