cmake_minimum_required(VERSION 2.6)
project(Web_Server)

set(CMAKE_CXX_STANDARD 17)

set(Boost_USE_STATIC_LIBS ON)

find_package(Boost REQUIRED)

add_subdirectory(src)
