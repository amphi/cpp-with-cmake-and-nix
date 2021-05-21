# Export interface target for catch2
find_package(Catch2 REQUIRED)
include(CTest)
include(Catch)

# Disable clang-tidy for this subfolder
set(CMAKE_CXX_CLANG_TIDY "")

add_library(catch_main STATIC catch_main.cpp)
target_link_libraries(catch_main PUBLIC project_warnings project_options
                                        Catch2::Catch2)

add_executable(bitmanipulation_test bitmanipulation_test.cpp)
target_link_libraries(bitmanipulation_test PRIVATE project_warnings project_options
                                                   catch_main bitmanipulation)

add_executable(rpn_parser_test rpn_parser_test.cpp)
target_link_libraries(rpn_parser_test PRIVATE project_warnings project_options
                                              catch_main rpn_parser)

# after compiling, you can run "ctest" to run all added tests

catch_discover_tests(bitmanipulation_test)
catch_discover_tests(rpn_parser_test)
