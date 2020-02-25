
cmake_minimum_required(VERSION 3.13)
project(virtual_toolbox_SD_2019_2020)
set(CMAKE_CXX_STANDARD 14)


add_executable(HardwareSkeletonCode
        src/HardwareSkeletonCode/HardwareCodeTester.cpp
        src/HardwareSkeletonCode/ToolScanner.cpp
        src/HardwareSkeletonCode/ToolScanner.h)

add_executable(RFIDDriverCode
        src/RFIDDriverCode/RFIDCodeTester.cpp
        src/RFIDDriverCode/ToolScanner.cpp
        src/RFIDDriverCode/ToolScanner.h)

add_executable(DatabaseTester
        "src/DatabaseTesting/DatabaseTester.cpp"
        "src/DatabaseTools/SQLiteDatabase.cpp"
        "src/DatabaseTools/SQLiteDatabase.h"
        sqlite3/sqlite3.c
        sqlite3/sqlite3.h
        "src/DatabaseTools/CallbackFunctions.cpp"
        "src/DatabaseTools/CallbackFunctions.h"
        src/HardwareSkeletonCode/ToolScanner.h
        src/HardwareSkeletonCode/ToolScanner.cpp)

add_executable(DatabaseMain
        src/DatabaseTesting/DatabaseMain.cpp
        "src/DatabaseTools/SQLiteDatabase.cpp"
        "src/DatabaseTools/SQLiteDatabase.h"
        sqlite3/sqlite3.c
        sqlite3/sqlite3.h
        "src/DatabaseTools/CallbackFunctions.cpp"
        "src/DatabaseTools/CallbackFunctions.h"
        src/HardwareSkeletonCode/ToolScanner.h
        src/HardwareSkeletonCode/ToolScanner.cpp)
