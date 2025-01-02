cmake_minimum_required(VERSION 3.22)
project(wlkatac VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 使用 GLOB 收集 wlkata/src 目录下的所有 .cc 文件
#Collect all. cc files in the wlkata/src directory using GLOB
file(GLOB WLKATA_SRC "${PROJECT_SOURCE_DIR}/wlkata/src/*.cc")

# 收集 serial/src 和 serial/src/impl 目录下的所有 .cc 文件
#Collect all. cc files in the serial/src and serial/src/impl directories using GLOB
file(GLOB SERIAL_SRC 
    "${PROJECT_SOURCE_DIR}/serial/src/*.cc"
    "${PROJECT_SOURCE_DIR}/serial/src/impl/*.cc"
    "${PROJECT_SOURCE_DIR}/serial/src/impl/list_ports/*.cc"
)

add_executable(wlkata main.cpp ${WLKATA_SRC} ${SERIAL_SRC})

#ubuntu请注释掉下面一行
#Ubuntu, please comment out the following line
target_link_libraries(wlkata SetupAPI)

include_directories(
    ${PROJECT_SOURCE_DIR}/wlkata/include
    ${PROJECT_SOURCE_DIR}/serial/include
)

