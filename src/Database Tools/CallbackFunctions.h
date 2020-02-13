//
// Created by MattTurconi on 2/11/2020.
//

#ifndef VIRTUAL_TOOLBOX_SD_2019_2020_CALLBACKFUNCTIONS_H
#define VIRTUAL_TOOLBOX_SD_2019_2020_CALLBACKFUNCTIONS_H

#include "SQLiteDatabase.h"
#include <iostream>
#include <string.h>




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

string getCallBackResponse();

vector<int> getNewIDVec();

#endif //VIRTUAL_TOOLBOX_SD_2019_2020_CALLBACKFUNCTIONS_H
