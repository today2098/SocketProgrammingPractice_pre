cmake_minimum_required(VERSION 3.16)
project(sock_prog_practice CXX)

add_library(utility STATIC src/library/die_with_message.cpp)

add_executable(client.out src/SimpleTcp/simple_tcp_client.cpp)
target_link_libraries(client.out utility)

add_executable(server.out src/SimpleTcp/simple_tcp_server.cpp)
target_link_libraries(server.out utility)
