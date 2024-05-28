cmake_minimum_required(VERSION 3.28)
project(keyauth)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_WARN_DEPRECATED OFF CACHE BOOL "" FORCE)
set(CMAKE_CXX_FLAGS /bigobj)

add_subdirectory(external/minhook)

add_library(keyauth SHARED
    main.cpp
)

target_link_libraries(keyauth PUBLIC libhat minhook ws2_32)
target_include_directories(keyauth PUBLIC )