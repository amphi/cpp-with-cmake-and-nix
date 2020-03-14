# Export interface target for catch2
find_package(Catch2 REQUIRED)
include(CTest)
include(Catch)

add_library(catch_main STATIC catch_main.cpp)
target_link_libraries(catch_main PUBLIC Catch2::Catch2)

add_executable(bitmanipulation_test bitmanipulation_test.cpp)
target_link_libraries(bitmanipulation_test PRIVATE project_warnings project_options
                                                   catch_main)

catch_discover_tests(bitmanipulation_test)
