//
// Created by MattTurconi on 2/11/2020.
//


#include "CallbackFunctions.h"

using namespace std;

string callbackResponse;
string selectResponse;
vector<string> newIDs;
vector<string> missingIDs;

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
        missingIDs.push_back(argv[0]);
    }else if(strcmp(cmdtype, "EXIST") == 0){
        callbackResponse = argv[0];
    }else if(strcmp(cmdtype, "NEW") == 0){
        newIDs.push_back(argv[0]);
    }else if(strcmp(cmdtype, "SELECT") == 0){
        int i;
        for(i = 0; i < argc; i ++){
            selectResponse += argv[i];
            if(i != argc - 1 )
                selectResponse += ", ";
        }
    }
    return 0;
}

string getSelectResponse(){
    string str = selectResponse;
    selectResponse = "";
    return str;
}


string getCallBackResponse(){
    string str = callbackResponse;
    callbackResponse = "";
    return str;
}

vector<string> getMissingIDVec(){
    vector<string> idxs = missingIDs;
//    int i;
//    for(i=0;i<idxs.size();i++){
//        cout<<to_string(idxs[i]) +',';
//    }
//    cout<<endl;
    missingIDs.clear();
    return idxs;
}

vector<string> getNewIDVec(){
    vector<string> idxs = newIDs;
//    int i;
//    for(i=0;i<idxs.size();i++){
//        cout<<to_string(idxs[i]) +',';
//    }
//    cout<<endl;
    newIDs.clear();
    return idxs;
}


