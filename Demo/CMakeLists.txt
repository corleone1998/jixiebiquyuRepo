#声明最低版本的cmake生成器
cmake_minimum_required(VERSION 3.5 )
#创建工程文件
project(demo)
#查找源文件路径变量
aux_source_directory(${PROJECT_SOURCE_DIR} SRC)
#将函数添加为库
add_library(Calcu STATIC calc.cpp)
#设置库的储存路径
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/ku)
#将库的路径链接进来
link_directories(${Calcu})
#链接库
link_libraries(Calcu)
#设置生成可执行文件的存放路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
#创建可执行文件
add_executable(demo demo.cpp)
#将生成的可执行文件指定存放路径
# set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")
set_target_properties(demo PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")