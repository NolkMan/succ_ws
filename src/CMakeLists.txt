add_executable(server server.cpp listener.cpp session.cpp)
target_link_libraries(server ${Boost_LIBRARIES})
target_link_libraries(server pthread)
