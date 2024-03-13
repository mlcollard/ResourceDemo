# @file CMakeLists.txt
# 
# CMake files for the Resource Demo example

cmake_minimum_required(VERSION 3.28 FATAL_ERROR)

project(ResourceDemo)

# resource_demo
add_executable(resource_demo)
target_sources(resource_demo PRIVATE ResourceDemo.cpp)
target_compile_features(resource_demo PRIVATE cxx_std_17)
target_compile_options(resource_demo PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/Wall>
    $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-Wall>
)

# run
add_custom_target(run
        COMMENT "Run"
        COMMAND $<TARGET_FILE:resource_demo> lines.txt
        DEPENDS resource_demo
        USES_TERMINAL
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)
