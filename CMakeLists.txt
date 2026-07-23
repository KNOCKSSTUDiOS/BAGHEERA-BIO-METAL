cmake_minimum_required(VERSION 3.10)
project(BAGHEERA_BIO_METAL CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Added src/include here so platform_bridge.hpp can be found
include_directories(include src/include)

file(GLOB SOURCES "src/*.cpp" "src_files/*.cpp")

add_executable(bagheera_engine ${SOURCES})
