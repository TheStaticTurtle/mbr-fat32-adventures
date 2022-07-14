cmake_minimum_required(VERSION 3.10)

# set the project name
project(disk_reader)

add_executable(disk_reader)

target_sources(disk_reader PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/mbr.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/fat.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/fat16.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/fat32.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/part.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/utf-convert.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pretty_print.cpp 
)

target_include_directories(disk_reader PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_options(disk_reader PUBLIC -Wno-address-of-packed-member)