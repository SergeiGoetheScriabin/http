cmake_minimum_required(VERSION 3.10)
project(http)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

set(SOURCES
    src/main.cpp
    src/tcp_server.cpp
    src/http_request.cpp
    src/http_response.cpp
    src/mime_types.cpp
)

add_executable(server ${SOURCES})

target_compile_options(server PRIVATE -Wall -Wextra)
