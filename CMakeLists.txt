cmake_minimum_required(VERSION 3.28)

project(Cpp20ThreadPoolLite VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(fmt REQUIRED)

add_executable(demo main.cpp)
target_link_libraries(demo fmt::fmt)
