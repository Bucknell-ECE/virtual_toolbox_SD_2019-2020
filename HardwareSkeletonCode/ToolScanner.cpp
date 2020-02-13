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
 * @param numTools specifies the number of scans to perform
 * @return a 2D list of integers representing the ID's found for each scan
 *
 * Returned list should be formatted as such:
 * The list should have the same number of rows as the parameter numScans.
 * Each row should correspond to a different scan.
 * Each row could have a varied number of columns. Each column should contain
 * a unique ID number stored as an int.
 */
vector<int> ToolScanner::scanForTools(){
    return {1,2,3,4};
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

