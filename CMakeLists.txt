cmake_minimum_required(VERSION 3.15)
project(option_pricing LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SRC "src/*.cpp")
include_directories(include)
add_library(option_pricing STATIC ${SRC})
