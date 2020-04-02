#create a new library and add the include folder to the include directories
add_library(rpn_parser STATIC rpn_parser.cpp)
target_include_directories(rpn_parser PUBLIC include)
target_link_libraries(rpn_parser PRIVATE project_warnings project_options)
