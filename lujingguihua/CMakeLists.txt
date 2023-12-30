cmake_minimum_required(VERSION 3.5)

project(lujing)

# 设置构建类型为 Debug 模式，包含调试信息
set(CMAKE_BUILD_TYPE Debug)

set(CXX_STANDARD_REQUIRED 11)
find_package(OpenCV REQUIRED) #不用预先设置包的寻找路径了，因为linux中已经将包添加到环境变量中了

include_directories("../include")

# add_library(AntColonyOptimization ${PROJECT_SOURCE_DIR}/src/AntColonyOptimization.cpp)

# #链接静态库文件
# link_directories(AntColonyOptimization)

add_executable(lujing "${PROJECT_SOURCE_DIR}/src/lujing.cpp" "${PROJECT_SOURCE_DIR}/src/AntColonyOptimization.cpp")

#链接动态库文件
target_link_libraries(lujing "${OpenCV_LIBS}")

set_target_properties(lujing PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

# 指定编译器选项
target_compile_options(lujing PRIVATE -g)

