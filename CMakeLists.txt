cmake_minimum_required(VERSION 2.8)
project(largeNumber)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g")
aux_source_directory(. DIR_TOOT_SRCS)

add_executable(largeNumber ${DIR_TOOT_SRCS})

