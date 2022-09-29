cmake_minimum_required(VERSION 3.16)
project(sock_prog_practice CXX)

# src/library
add_library(utility STATIC src/library/die_with_message.cpp)

# src/SimpleTcp
add_executable(simple_tcp_client.out src/SimpleTcp/simple_tcp_client.cpp)
target_link_libraries(simple_tcp_client.out utility)

add_executable(simple_tcp_server.out src/SimpleTcp/simple_tcp_server.cpp)
target_link_libraries(simple_tcp_server.out utility)

# src/test
add_executable(getaddrinfo.out src/test/getaddrinfo.cpp)
add_executable(perror.out src/test/perror.cpp)
