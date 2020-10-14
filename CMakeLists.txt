cmake_minimum_required(VERSION 3.17)
project(opencv)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 14)
find_package (ZBar0 REQUIRED)
find_package( OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
add_executable( opencv main.cpp)
target_link_libraries( opencv ${OpenCV_LIBS} ${ZBAR_LIBRARIES})