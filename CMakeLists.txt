cmake_minimum_required(VERSION 3.16)
project(info_sec)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)
add_subdirectory(third-party)
add_subdirectory(test)

add_library(info_sec_include INTERFACE)
target_include_directories(info_sec_include INTERFACE
    include
)

add_executable(rsa src/main.cpp)
target_link_libraries(rsa PUBLIC
    info_sec_include
    info_sec_dummy
    info_sec_rsa
    info_sec_math
)
