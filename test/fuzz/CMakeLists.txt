# Disable clang-tidy for this subfolder
set(CMAKE_CXX_CLANG_TIDY "")

if(NOT CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    find_program(CLANG++ clang++)
    if(CLANG++)
        set(CMAKE_CXX_COMPILER ${CLANG++})
    else()
        message(STATUS "Could not find clang++, skipping fuzz-testing.")
        return()
    endif()
endif()

# it looks like i can not overwrite the project_warnings in case i am not using
# clang already
add_library(fuzz_warnings INTERFACE)
set_clang_project_warnings(fuzz_warnings)

add_executable(rpn_parser_fuzz_test rpn_parser_test.cpp)
target_link_libraries(rpn_parser_fuzz_test PRIVATE fuzz_warnings project_options rpn_parser
                                                   -coverage -fsanitize=fuzzer)
target_compile_options(rpn_parser_fuzz_test PRIVATE -fsanitize=fuzzer)

set(FUZZ_RUNTIME 10 CACHE STRING "Number of seconds to run fuzz test during ctest run")

add_test(NAME rpn_parser_fuzz_test COMMAND rpn_parser_fuzz_test -max_total_time=${FUZZ_RUNTIME})
