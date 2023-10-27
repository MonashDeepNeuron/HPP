cmake_minimum_required(VERSION 3.14...3.27)

project(
    HelloCMakeProject
    VERSION 0.1.0
    DESCRIPTION "Sample CMake Hello World Project"
    LANGUAGES CXX
)

add_executable(HelloCMake hello-cmake.cxx)
target_compile_features(HelloCMake PRIVATE cxx_std_20)
