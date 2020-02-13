
cmake_minimum_required(VERSION 3.13)
project(virtual_toolbox_SD_2019_2020)
set(CMAKE_CXX_STANDARD 14)


add_executable(HardwareSkeletonCode HardwareSkeletonCode/HardwareCodeTester.cpp
        HardwareSkeletonCode/ToolScanner.cpp
        HardwareSkeletonCode/ToolScanner.h)

add_executable(RFIDDriverCode RFIDDriverCode/RFIDCodeTester.cpp
        RFIDDriverCode/ToolScanner.cpp
        RFIDDriverCode/ToolScanner.h)

add_executable(DatabaseTester "src/Database Tools/DatabaseTester.cpp"
        "src/Database Tools/SQLiteDatabase.cpp"
        "src/Database Tools/SQLiteDatabase.h"
        sqlite3/sqlite3.c
        sqlite3/sqlite3.h
        "src/Database Tools/CallbackFunctions.cpp"
        "src/Database Tools/CallbackFunctions.h"
        HardwareSkeletonCode/ToolScanner.h
        HardwareSkeletonCode/ToolScanner.cpp)
