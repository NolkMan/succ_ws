set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})#/bin/client/${CMAKE_BUILD_TYPE})

add_executable(server server.cpp listener.cpp session.cpp web_socket_server.cpp)
target_link_libraries(server ${Boost_LIBRARIES})
target_link_libraries(server pthread)
