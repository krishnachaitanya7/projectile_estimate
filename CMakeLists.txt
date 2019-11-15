cmake_minimum_required(VERSION 3.15)
project(projectile_estimate)
set(CMAKE_CXX_STANDARD 17)
find_package(OpenCV REQUIRED)
# This should be present at this location
# Basically I installed everything manually
## Along with udev rules, so god help me
#include_directories("/usr/local/include/librealsense2")
#link_directories("/usr/local/lib")
include_directories($(PROJECT_SOURCE_DIR)/include/realsense_camera)
include_directories($(PROJECT_SOURCE_DIR)/include/constants)
add_executable(projectile_estimate main.cpp src/realsense_camera/cam.cpp)
target_link_libraries(projectile_estimate realsense2 pthread ${OpenCV_LIBS})