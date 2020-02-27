//
// Created by MattTurconi on 2/5/2020.
//
/**
 * This file is part of the Virtual Toolbox system.
 *
 * Developed for the Oshkosh companies JLG and Jerr Dan.
 * This project is a sponsored senior design project for
 * Electrical and Computer Engineering Students at Bucknell
 * University during the 2019 - 2020 Academic Year.
 */


/**
 * Any include statements should go into your header file. Then you only have
 * write this include statement and no other include statements
 * Same goes for any #define statements for Macro values.
 */
#include "ToolScanner.h"
#include <string.h>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <typeinfo>
#include <iterator>
#include <sstream>
#include <string>
#include <unistd.h>
#include <algorithm>
using namespace std;


/**
 * This is where you will actually write your functions
 * Feel free to make additional files and helper methods if this
 * file gets too big. Try your best to not exceed 500 lines of code.
 * It will make for difficult to read code.
 */

//TODO Implement all your functions
//TODO Add documentation

/**
 * Implicit Constructor for the Class
 */
ToolScanner::ToolScanner() {
    printf("Created Object\n");
}

/**
    * Scans the physical tool box for present tools.
    *
    * @return a list of integers representing the ID's that are in the ToolBox
    *
    * The returned list is assumed to have a complete and accurate list of tool
    * IDs that are in the physical ToolBox.
    */
vector<string> ToolScanner::scanForTools(){
    //make csv in python
    system("python mult.py");
	
    std::ifstream       file("uid.csv");
	
	
    std::vector<std::string>   result;
    std::string                line;
    std::getline(file,line);

    std::stringstream          lineStream(line);
    std::string                cell;

    while(std::getline(lineStream,cell, ','))
    {
        result.push_back(cell);
    }
    // This checks for a trailing comma with no data after it.
    if (!lineStream && cell.empty())
    {
        // If there was a trailing comma then add an empty element.
        result.push_back("");
    }
    
    return result;
}

/**
 * This is just a placeholder for a setup function.
 * You should change this to fit your system's setup needs
 * based on parameters that need called to set up the scanner.
 * This function should likely be called on creation of the object.
 *
 * You may also want to handle some sort of fatal error that occurs if
 * the scanner is not physically connected to the PI correctly.
 */
void ToolScanner::setupScanner(){

}

//TODO Write any getters and setters
//TODO Write any helper methods
