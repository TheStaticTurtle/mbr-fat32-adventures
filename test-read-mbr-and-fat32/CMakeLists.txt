cmake_minimum_required(VERSION 3.10)

# set the project name
project(disk_reader)

add_executable(disk_reader)

target_sources(disk_reader PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/mbr.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/fat.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/part.cpp 
)

target_include_directories(disk_reader PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)