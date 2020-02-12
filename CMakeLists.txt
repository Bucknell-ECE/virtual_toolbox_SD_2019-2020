
cmake_minimum_required(VERSION 3.13)
project(virtual_toolbox_SD_2019_2020)
set(CMAKE_CXX_STANDARD 14)

add_executable(DatabaseTester src/database/DatabaseTester.cpp
        src/database/SQLiteDatabase.cpp
        src/database/SQLiteDatabase.h
        sqlite3/sqlite3.c
        sqlite3/sqlite3.h src/database/CallbackFunctions.cpp src/database/CallbackFunctions.h)
