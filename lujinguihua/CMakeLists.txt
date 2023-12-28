cmake_minimum_required(VERSION 3.5)

project(lujing)
set(CXX_STANDARD_REQUIRED 11)
find_package(OpenCV REQUIRED) #不用预先设置包的寻找路径了，因为linux中已经将包添加到环境变量中了

add_executable(lujing "${PROJECT_SOURCE_DIR}/antcolony.cpp")

set_target_properties(lujing PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

target_link_libraries(lujing "${OpenCV_LIBS}")

