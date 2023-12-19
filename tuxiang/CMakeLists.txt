# 声明要求的cmake最低版本
cmake_minimum_required(VERSION 3.5)
# 生成工程名及其（版本号）
project(tuxiang)

# 将所有源文件.cpp放在配置文件的src文件夹下是不行的，因为cmake只注重构建系统的生成，而源文件通过其他工具来处理，比如终端命令行
    # 现找到当前目录下的所有源文件
    # file(GLOB My_source "${PROJECT_SOURCE_DIR}/*.cpp" )
    # # 设置其路径为src
    # set(My_source "${PROJECT_SOURCE_DIR}/src")

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
# 找包
find_package(OpenCV REQUIRED)
# 生成可执行文件
add_executable(Map ${PROJECT_SOURCE_DIR}/src/Map.cpp)
# 将可执行文件放在当前路径的bin文件下
set_target_properties(Map PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
# 包含头文件
# include_directories(${OpenCV_INCLUDE_DIRS})
# 打印头文件的值
message(${OpenCV_INCLUDE_DIRS})
# 链接动态库
target_link_libraries(Map ${OpenCV_LIBS})
#打印 OpenCV_LIBS 变量的值。
message(${OpenCV_LIBS})
#  OpenCV_DIR 变量的值。
message(${OpenCV_DIR})
