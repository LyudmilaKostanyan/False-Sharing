cmake_minimum_required(VERSION 3.10)

project(False-Sharing)

add_executable(main main.cpp)
set_property(TARGET main PROPERTY CXX_STANDARD 20)