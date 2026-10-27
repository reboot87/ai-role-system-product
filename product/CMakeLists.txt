cmake_minimum_required(VERSION 3.10)
project(swf_parser)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(swf_parser
    src/swf_parser.cpp
    src/main.cpp
)
