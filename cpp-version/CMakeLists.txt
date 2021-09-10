cmake_minimum_required (VERSION 3.11...3.21)
project (json_example
    VERSION 0.1
    DESCRIPTION "An example json project"
    LANGUAGES CXX)

if (CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ansi -pedantic -Wall")
endif()

add_subdirectory(src)

add_subdirectory(tests)