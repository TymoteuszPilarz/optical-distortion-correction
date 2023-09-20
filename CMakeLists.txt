cmake_minimum_required(VERSION 3.24)
project(optical_distortion_correction)

set(CMAKE_CXX_STANDARD 20)

add_executable(optical_distortion_correction Application.cpp MainFrame.cpp MainFrame.h Application.h)

find_package(wxWidgets REQUIRED gl core base OPTIONAL_COMPONENTS net)
include(${wxWidgets_USE_FILE})
target_link_libraries(optical_distortion_correction ${wxWidgets_LIBRARIES})
