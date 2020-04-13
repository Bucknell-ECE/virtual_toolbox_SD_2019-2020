//
// Created by MattTurconi on 2/11/2020.
//

#ifndef VIRTUAL_TOOLBOX_SD_2019_2020_CALLBACKFUNCTIONS_H
#define VIRTUAL_TOOLBOX_SD_2019_2020_CALLBACKFUNCTIONS_H

#include <vector>
#include <iostream>
#include <string.h>
#include <string>
#include "Tool.h"

using namespace std;



/**
 * A call back function for the SQL call. This function is called when the SQL call
 * is finished.
 *
 * @param data pointer that is passed to the sqlite3_exec command that could be used
 * as a way to determine how this function operates based on sql call
 * @param argc the number of data arguments for this call
 * @param argv the data returned by the sql call
 * @param columnNames
 * @return a 0 on success, 1 on error
 */
int callback(void *data, int argc, char **argv, char **columnNames);

/**
 * Used to retrieve a generic callback string value mainly used for debugging
 * purposes.
 *
 * @return A Debugging Keyword
 */
string getCallBackResponse();

/**
 * After a select call to the sqlite database, this function allows for
 * singular retrieval of the result separated by commas.
 *
 * @return A comma separated string
 */
string getSelectResponse();

/**
 * Used to retrieve a vector of string ID's that correspond to tools that
 * were not found in the database. This list indicates which tools are
 * currently missing from the toolbox.
 *
 * @return A vector of Tool ID's as Strings
 */
vector<Tool> getMissingIDVec();

/**
 * Used to retrieve a vector of a unique String ID that is new to the the
 * tool database for registration purposes.
 *
 * @return A vector with a new Tool ID as a String
 */
vector<string> getNewIDVec();


#endif //VIRTUAL_TOOLBOX_SD_2019_2020_CALLBACKFUNCTIONS_H
