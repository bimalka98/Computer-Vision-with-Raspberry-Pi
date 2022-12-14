# Cmake finalized
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
add_executable(${PROJECT_NAME} 
	main.cpp
    ${CMAKE_SOURCE_DIR}/facedetector.cpp
    )
# external library
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})

# Introduce preprocessor variables to keep paths of asset files
set(FACE_DETECTION_CONFIGURATION "${PROJECT_SOURCE_DIR}/assets/deploy.prototxt")
set(FACE_DETECTION_WEIGHTS "${PROJECT_SOURCE_DIR}/assets/res10_300x300_ssd_iter_140000_fp16.caffemodel")

target_compile_definitions(${PROJECT_NAME} PRIVATE FACE_DETECTION_CONFIGURATION="${FACE_DETECTION_CONFIGURATION}")
target_compile_definitions(${PROJECT_NAME} PRIVATE FACE_DETECTION_WEIGHTS="${FACE_DETECTION_WEIGHTS}")

