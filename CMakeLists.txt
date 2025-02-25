cmake_minimum_required(VERSION 3.10)
project(DisplayTest)

set(CMAKE_CXX_STANDARD 17)

find_library(RT_LIB rt REQUIRED)
find_library(GPIOD_LIB gpiod REQUIRED)

add_executable(DisplayTest main.cpp
        display.cpp
        display.h
        gpio.cpp
        gpio.h
        bitmapDisplay.cpp
        bitmapDisplay.h)
target_link_libraries(DisplayTest ${GPIOD_LIB} ${RT_LIB})
