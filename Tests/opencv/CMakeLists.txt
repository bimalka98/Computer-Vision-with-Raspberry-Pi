cmake_minimum_required(VERSION 3.1)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# set the project name
project(cpp_opencv_test)

# find OpenCV library
find_package(OpenCV REQUIRED)

# target 
add_executable(cpp_opencv_test main.cpp)

# external library linking
target_link_libraries(cpp_opencv_test ${OpenCV_LIBS})
