cmake_minimum_required(VERSION 3.23.2)
project(Cinema_Booking_System)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Cinema_Booking_System
        main.cpp
        menuSelection.hpp
        seatArrangement.hpp)
