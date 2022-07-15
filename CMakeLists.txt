cmake_minimum_required(VERSION 3.0)
project(SLAM-HongBeom)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE "Release")


find_package(OpenCV REQUIRED)
find_package(Eigen3 3.1.0 REQUIRED)
find_package(Pangolin REQUIRED)

include_directories(
    include
    ${Opencv_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
    ${Pangolin_INCLUDE_DIRS}
)

add_executable(vio_test 
                src/main.cpp
                src/utils.cpp)
target_link_libraries(vio_test ${OpenCV_LIBS} ${EIGEN3_LIBS} ${Pangolin_LIBRARIES})

