﻿# CMakeList.txt : CMake project for SDL2Project, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (SDL2Project "main.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET SDL2Project PROPERTY CXX_STANDARD 20)
endif()
