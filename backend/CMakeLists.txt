cmake_minimum_required(VERSION 3.15)
project(ServidorBackend LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

find_package(Threads REQUIRED)

add_executable(servidor
    main.cpp
    huffman.cpp
    Node.cpp
)

target_link_libraries(servidor PRIVATE
    Threads::Threads
    ws2_32
    wsock32
    mswsock
)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)