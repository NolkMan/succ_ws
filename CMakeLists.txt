cmake_minimum_required(VERSION 3.13)
project(Web_Server)

set(CMAKE_CXX_STANDARD 17)

set(Boost_USE_STATIC_LIBS ON)

find_package(Boost REQUIRED COMPONENTS system)
include_directories( ${Boost_INCLUDE_DIRS} )
link_directories( ${Boost_LIBRARY_DIRS} )

find_package(Threads)

add_subdirectory(src)

#add_executable(server server.cpp listener.cpp session.cpp)
#target_link_libraries(server ${Boost_LIBRARIES})
#target_link_libraries(server pthread)
