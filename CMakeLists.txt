cmake_minimum_required(VERSION 3.16)
project(sock_prog_practice)

# src/library
add_library(utility STATIC src/library/die_with_message.c)

# src/SimpleTcp
add_executable(simple_tcp_client.out src/SimpleTcp/simple_tcp_client.c)
target_link_libraries(simple_tcp_client.out utility)

add_executable(simple_tcp_client_with_name_resolution.out src/SimpleTcp/simple_tcp_client_with_name_resolution.c)
target_link_libraries(simple_tcp_client_with_name_resolution.out utility)

add_executable(simple_tcp_server.out src/SimpleTcp/simple_tcp_server.c)
target_link_libraries(simple_tcp_server.out utility)

# src/FT
add_executable(ft_client.out src/FT/ft_client.c)
target_link_libraries(ft_client.out utility)

add_executable(ft_client_with_name_resolution.out src/FT/ft_client_with_name_resolution.c)
target_link_libraries(ft_client_with_name_resolution.out utility)

add_executable(ft_server.out src/FT/ft_server.c)
target_link_libraries(ft_server.out utility)

# src/test
add_executable(getaddrinfo.out src/test/getaddrinfo.c)

add_executable(perror.out src/test/perror.c)
