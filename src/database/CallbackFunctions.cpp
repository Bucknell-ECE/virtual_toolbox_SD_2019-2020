//
// Created by MattTurconi on 2/11/2020.
//


#include "CallbackFunctions.h"



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
int callback(void *data, int argc, char **argv, char **columnNames){
    int i;
    char* cmdtype = (char*) data;
    cout << print_cols << endl;
    if(print_cols){
        string str = "";
        for(i = 0; i < argc; i++){
            str += columnNames[i];
            str += "   ";
        }
        cout << str << endl;
        print_cols = 0;
    }

    string str = "";
    for(i = 0; i < argc; i++){
        str += argv[i];
        str += "   ";
    }
    cout << str << endl;
    return 0;
}