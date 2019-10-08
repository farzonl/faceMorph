cmake_minimum_required(VERSION 3.4.3)
project(face-morph)

find_package( OpenCV REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable(face-morph main.cpp)
target_link_libraries( face-morph ${OpenCV_LIBS} )
set(CMAKE_CXX_FLAGS "-std=c++11")

