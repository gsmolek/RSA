cmake_minimum_required(VERSION 3.0)
project(rsa)

add_library(rsa src/rsa.cpp)
target_include_directories(rsa PUBLIC include/)
