cmake_minimum_required(VERSION 3.24)
project(optical_distortion_correction)

set(CMAKE_CXX_STANDARD 20)

add_executable(optical_distortion_correction src/Application.h src/Application.cpp src/MainFrame.cpp src/MainFrame.h src/DistortionEngine.cpp src/DistortionEngine.h src/ImagePanel.cpp src/ImagePanel.h src/MenuBar.cpp src/MenuBar.h src/ControlPanel.cpp src/ControlPanel.h src/Page.cpp src/Page.h src/Element.cpp src/Element.h)

find_package(wxWidgets REQUIRED gl core base)
include(${wxWidgets_USE_FILE})
target_link_libraries(optical_distortion_correction ${wxWidgets_LIBRARIES})

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(optical_distortion_correction ${OpenCV_LIBS})