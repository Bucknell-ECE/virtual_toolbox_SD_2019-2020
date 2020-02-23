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



#ifndef VIRTUAL_TOOLBOX_SD_2019_2020_TOOLSCANNER_H
#define VIRTUAL_TOOLBOX_SD_2019_2020_TOOLSCANNER_H

#include <stdio.h>
#include <vector>
using namespace std;

/**
 * The ToolScanner class will allow the backend of the virtual toolbox
 * to communicate with physical hardware.
 */
class ToolScanner {
    /**
     * These are where you will store variables specific to your class.
     * They are marked as private so they can not be accessed outside of the class
     * Provide comments for each variable you define
     */
private:
    //TODO Define any attributes that this class will have specific to your implementation
    //TODO Define any class constants here

    /**
     * This is where functions that are able to be called on your object are specified
     * So things like the constructor, any setup methods that need to be called,
     * and most importantly the data retrieval method that will return the tool ID's
     */
public:
    /**
     * The implicit constructor for the class.
     */
    ToolScanner();

    /**
    * Scans the physical tool box for present tools.
    *
    * @return a list of integers representing the ID's that are in the ToolBox
    *
    * The returned list is assumed to have a complete and accurate list of tool
    * IDs that are in the physical ToolBox.
    */
     vector<string> scanForTools();

    /**
     * This is just a placeholder for a setup function.
     * You should change this to fit your system's setup needs
     * based on parameters that need called to set up the scanner.
     * This function should likely be called on creation of the object.
     *
     * You may also want to handle some sort of fatal error that occurs if
     * the scanner is not physically connected to the PI correctly.
     */
    void setupScanner();

    //TODO if needed put your helper functions here. Add documentation
    //TODO define any getters and setters for each private variable.
};


#endif //VIRTUAL_TOOLBOX_SD_2019_2020_TOOLSCANNER_H
