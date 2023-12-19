cmake_minimum_required(VERSION 3.5)

project(fenge2)
set(CXX_STANDARD_REQUIRED 11)
find_package(OpenCV REQUIRED) #不用预先设置包的寻找路径了，因为linux中已经将包添加到环境变量中了

add_executable(fenge2 "${PROJECT_SOURCE_DIR}/src/K-means2.cpp")

set_target_properties(fenge2 PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

target_link_libraries(fenge2 "${OpenCV_LIBS}")
#不用包含头文件了，因为c++的配置文件已经设置好了


