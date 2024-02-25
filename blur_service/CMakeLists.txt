cmake_minimum_required(VERSION 3.24)
PROJECT(blur)

FIND_PACKAGE( opencv REQUIRED )
INCLUDE_DIRECTORIES( ${OpenCV_INCLUDE_DIRS} )
# target link opencv_....
ADD_EXECUTABLE(main main.cpp)
TARGET_LINK_LIBRARIES (main ${OpenCV_LIBS})