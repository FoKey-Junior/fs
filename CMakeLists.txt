cmake_minimum_required(VERSION 3.26)
project(fs LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(fs
        src/main.cpp
        src/FileManager.cpp
        src/DisplayManager.cpp
)

target_include_directories(fs
        PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)
