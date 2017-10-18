cmake_minimum_required(VERSION 3.8)
project(timer_list)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Timer.h
        TimerList.cpp
        TimerList.h
        main.cpp)

add_executable(timer_list ${SOURCE_FILES})