cmake_minimum_required(VERSION 3.21)
project(libwav_example C)

set(CMAKE_C_STANDARD 99)

add_executable(libwav_example main.c wavUtils.c)

find_library(yalibwav libyalibwav.so)
message(STATUS ${yalibwav})
target_link_libraries(libwav_example yalibwav)
