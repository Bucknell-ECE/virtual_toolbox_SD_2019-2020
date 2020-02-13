//
// Created by MattTurconi on 2/11/2020.
//


#include "CallbackFunctions.h"

string callbackResponse;
vector<int> newIDs;

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
    char* cmdtype = (char*) data;
//    cout<<cmdtype<<endl;
    if(strcmp(cmdtype, "DUMP") == 0){
        int i;
        if(callbackResponse.size() == 0){
            string str = "";
            for(i = 0; i < argc; i++){
                str += columnNames[i]; str += "   ";
            }
            cout << str << endl;
            callbackResponse = "DUMPED";
        }

        string str = "";
        for(i = 0; i < argc; i++){
            str += argv[i]; str += "   ";
        }
        cout << str << endl;
    }else if(strcmp(cmdtype, "MISS") == 0){
        int i;
        for(i = 0; i < argc; i++) {
            callbackResponse += (argv[i]);
            callbackResponse += ",";
        }
    }else if(strcmp(cmdtype, "EXIST") == 0){
        callbackResponse = argv[0];
    }else if(strcmp(cmdtype, "NEW") == 0){
        int i;
        for(i = 0; i < argc; i++) {
            newIDs.push_back(stoi(argv[i]));
        }
    }
    return 0;
}


string getCallBackResponse(){
    string str = callbackResponse;
    callbackResponse = "";
    return str;
}

vector<int> getNewIDVec(){
    vector<int> idxs = newIDs;
    int i;
    for(i=0;i<idxs.size();i++){
        cout<<to_string(idxs[i]) +',';
    }
    cout<<endl;
    newIDs.clear();
    return newIDs;
}


