cmake_minimum_required(VERSION 3.13)
project(virtual_toolbox_SD_2019_2020)
set(CMAKE_CXX_STANDARD 14)

add_executable(HardwareSkeletonCode HardwareSkeletonCode/HardwareCodeTester.cpp
        HardwareSkeletonCode/ToolScanner.cpp
        HardwareSkeletonCode/ToolScanner.h)

add_executable(RFIDDriverCode RFIDDriverCode/RFIDCodeTester.cpp
        RFIDDriverCode/ToolScanner.cpp
        RFIDDriverCode/ToolScanner.h)
