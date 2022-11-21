cmake_minimum_required(VERSION 3.1)

# set the project name
project(face_detection)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# specify dir path 
set(CMAKE_SOURCE_DIR src/)
set(CMAKE_BINARY_DIR ${PROJECT_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# headers
set(HEADER_FILES 
    ${CMAKE_SOURCE_DIR}/facedetector.hpp
)

# OpenCV library
find_package(OpenCV REQUIRED)

# target
add_executable(detect_faces 
	main.cpp
    ${CMAKE_SOURCE_DIR}/facedetector.cpp
    )
# external library
target_link_libraries(detect_faces ${OpenCV_LIBS})