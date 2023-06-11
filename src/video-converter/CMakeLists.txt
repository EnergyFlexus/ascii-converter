cmake_minimum_required(VERSION 3.0)
project(video-converter)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../../../build-video-converter)

add_executable(video-converter main.cpp VideoConverter.cpp)

set(OpenCV_DIR ./../opencv/build)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(video-converter ${OpenCV_LIBS})