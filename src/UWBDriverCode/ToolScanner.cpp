//
// Created by MattTurconi on 2/5/2020.
// Edited by Owen Meng on 02/25/2020
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
    // Set timer
    time_t start,end;
    double elapsed;
    start = time(NULL);
    int terminate = 1;
    
    // Buffer to store strings of tools in the truck
    vector<string> vec;
    
    // Run until timer ends
    while (terminate) {
        if (DEBUG) {
            std::cout << "Loop again \n";
        }
        strcpy(str,"");
        ch = serialGetchar(fd);
        while (ch != '\n') {
            strncat(str,&ch,1);
            ch = serialGetchar(fd);
        }
        
        if (DEBUG) {
            std::cout << "Data Received \n";
        }
        
        // Rocord the correctly formated position update
        if ((strstr(str, "POS") != NULL) && (strstr(str, " ") == NULL)) {
            tok = strtok(str,",");
            tok = strtok(NULL,",");
            tok = strtok(NULL,",");
            sscanf(tok,"%x",&tag_name);
            tok = strtok(NULL,",");
            tag_x = (int) (1000*atof(tok));
            tok = strtok(0,",");
            tag_y = (int) (1000*atof(tok));
            tok = strtok(0,",");
            tag_z = (int) (1000*atof(tok));
            tok = strtok(0,",");
            tag_quality = atof(tok);
            
            if (isInTruck(tag_x,tag_y,tag_z,tag_quality)) {
                vec.push_back(to_string(tag_name));
                if (DEBUG) {
                    std::cout << tag_name << " is in\n";
                }
            } else {
                if (DEBUG) {
                    std::cout << tag_name << " is out\n";
                }
            }
        }
        
        // Update the timer
        end = time(NULL);
        elapsed = difftime(end,start);
        if (elapsed >= 5 /* seconds */) {
            terminate = 0;
        }
    }
    return removeDuplicates(vec);
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
    // Setup UART and wiringPi
    if ((fd = serialOpen("/dev/serial0",115200))<0){
        fprintf(stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
        // return 1 ; // I don't know what to put here
    }
    if (wiringPiSetup () == -1) {
        fprintf (stdout, "Unable to start wiringPi: %s\n", strerror (errno)) ;
        // return 1 ;
    }

    // Enter UART shell mode
	serialPrintf(fd,"\r\r");
    delay(1000);
    // Activate listener mode
    serialPrintf(fd,"lec\r");
    delay(100);
    serialPrintf(fd,"lep\r");
    delay(100);
}

//TODO Write any getters and setters
//TODO Write any helper methods

bool ToolScanner::isInTruck(int x,int y,int z, int q) {
    if (q != 0)
        if ((X_MIN-D)<x)
            if (x<(X_MAX+D))
                if ((Y_MIN-D)<y)
                    if (y<(Y_MAX+D))
                        if ((Z_MIN-D)<z)
                            if (z<(Z_MAX+D))
                                return true;
    return false;
}

vector<string> ToolScanner::removeDuplicates(vector<string> vec) {
    sort(vec.begin(),vec.end());
    vec.erase(unique(vec.begin(),vec.end()),vec.end());
    return vec;
}

