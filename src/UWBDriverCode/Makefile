CC = g++
CFLAGS = -Wall -g -lwiringPi
SQLFLAGS = -pthread -ldl

all: HardwareCodeTester

ToolScanner.o: ToolScanner.h ToolScanner.cpp
	$(CC) $(CFLAGS) -c ToolScanner.cpp
	
HardwareCodeTester.o: HardwareCodeTester.cpp
	$(CC) $(CFLAGS) -c HardwareCodeTester.cpp
	
HardwareCodeTester: ToolScanner.o HardwareCodeTester.o
	$(CC) $(CFLAGS) -o HardwareCodeTester HardwareCodeTester.o ToolScanner.o
