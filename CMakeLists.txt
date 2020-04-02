cmake_minimum_required(VERSION 3.15)

# most of this is taken from github.com/lefticus/cpp_starter_project

# Set the project name and include standard settings
project(my_cpp_project CXX)
include(cmake/StandardProjectSettings.cmake)

# Link this 'library' to set the c++ standard / compile-time options requested
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_17)

# standard compiler warnings
include(cmake/CompilerWarnings.cmake)

# Link this 'library' to use the warnings specified in CompilerWarnings.cmake
add_library(project_warnings INTERFACE)
set_default_project_warnings(project_warnings)

# include static analysis
include(cmake/StaticAnalysis.cmake)

# sanitizer options if supported by compiler
include(cmake/Sanitizers.cmake)
enable_sanitizers(project_options)

add_subdirectory(lib)

option(ENABLE_TESTING "Enable Test Builds" ON)
if(ENABLE_TESTING)
    enable_testing()
    message(STATUS "Building Tests enabled.")
    add_subdirectory(test)
endif()

add_subdirectory(app)
