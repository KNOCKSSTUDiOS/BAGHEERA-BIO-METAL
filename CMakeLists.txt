cmake_minimum_required(VERSION 3.10)
project(BAGHEERA_BIO_METAL CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Headers live in include/, sources in src/ -- explicit list, no globbing.
set(SOURCES
    src/main.cpp
    src/app_core.cpp
    src/config_parser.cpp
    src/system_io.cpp
    src/platform_bridge.cpp
    src/system_diag.cpp
)

add_executable(bagheera_engine ${SOURCES})

target_include_directories(bagheera_engine PRIVATE include)

target_link_libraries(bagheera_engine PRIVATE pthread)

# Link std::filesystem on older toolchains that split it into a separate library.
find_library(STDCXX_FS stdc++fs)
if(STDCXX_FS)
    target_link_libraries(bagheera_engine PRIVATE ${STDCXX_FS})
endif()
