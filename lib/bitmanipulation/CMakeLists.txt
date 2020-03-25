#create a new library and add the include folder to the include directories
add_library(bitmanipulation STATIC bitmanipulation.cpp)
target_include_directories(bitmanipulation PUBLIC include)
