add_executable(test test.cpp)

# I'm using C++17 in the test
target_compile_features(test PRIVATE cxx_std_17)

# Should be linked to the main library, as well as the Catch2 testing library
target_link_libraries(test PRIVATE json_library)

