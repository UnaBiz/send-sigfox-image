cmake_minimum_required(VERSION 3.6)
project(jpeg_decoder)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp ../JPEGDecoder.cpp ../CameraReader.cpp ../picojpeg.c)
add_executable(jpeg_decoder ${SOURCE_FILES})