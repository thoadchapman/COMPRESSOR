cmake_minimum_required(VERSION 3.15)

# Export compile_commands.json for clangd/IDE IntelliSense
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

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

target_include_directories(servidor PRIVATE
    include
    C:/msys64/ucrt64/include
    C:/msys64/ucrt64/include/c++/16.1.0
    C:/msys64/ucrt64/include/c++/16.1.0/x86_64-w64-mingw32
    C:/msys64/ucrt64/include/c++/16.1.0/backward
    C:/msys64/ucrt64/x86_64-w64-mingw32/include
)

target_link_libraries(servidor PRIVATE
    Threads::Threads
    ws2_32
    wsock32
    mswsock
)