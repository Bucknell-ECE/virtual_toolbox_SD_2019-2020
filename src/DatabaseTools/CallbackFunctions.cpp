//
// Created by MattTurconi on 2/11/2020.
//


#include "CallbackFunctions.h"

using namespace std;

string callbackResponse;
string selectResponse;
vector<string> newIDs;
vector<string> missingIDs;
vector<int> priorityList;

void insertInToolList(int priority, string basicString);

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
    }else if(strcmp(cmdtype, "MISS") == 0) {
        missingIDs.push_back(argv[0]);
    }else if(strcmp(cmdtype, "MISSP") == 0){
        int priority = atoi(argv[1]);
        string tool = argv[0];
        insertInToolList(priority, tool);
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

void insertInToolList(int priority, string basicString) {
    auto itID = missingIDs.begin();
    auto itP = priorityList.begin();
    if(priorityList.size() == 0){
        priorityList.push_back(priority);
        missingIDs.push_back(basicString);
        return;
    }

    int i;
    for(i = 0; i < priorityList.size(); i++){
        if(priorityList[i] < priority) {
            itID++;
            itP++;
        }else
            break;
    }
    missingIDs.insert(itID, basicString);
    priorityList.insert(itP, priority);
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
    missingIDs.clear();
    priorityList.clear();
    return idxs;
}

vector<string> getNewIDVec(){
    vector<string> idxs = newIDs;
    newIDs.clear();
    return idxs;
}

vector<int> getPriorityVec(){
    int i;
    for(i = 0; i < priorityList.size(); i ++){
        cout << priorityList[i] << ", ";
    }
    cout << endl;
}
