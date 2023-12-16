cmake_minimum_required(VERSION 3.5)
project(tuxiang)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)

add_executable(map1 map1.cpp)

include_directories(${OpenCV_INCLUDE_DIRS})
message(${OpenCV_INCLUDE_DIRS})



target_link_libraries(map1 ${OpenCV_LIBS})
message(${OpenCV_LIBS})
message(${OpenCV_DIR})
