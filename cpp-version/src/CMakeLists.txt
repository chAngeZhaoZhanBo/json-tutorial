

add_library(json_library JsonObject.cpp JsonParser.cpp)

target_include_directories(json_library PUBLIC ../include)

target_compile_features(json_library PUBLIC cxx_std_17)

target_compile_options(json_library PUBLIC -Wall -O3)

