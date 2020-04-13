//
// Created by MattTurconi on 2/11/2020.
//


#include "CallbackFunctions.h"
#include "Tool.h"

using namespace std;

string callbackResponse;
string selectResponse;
vector<string> newIDs;
vector<Tool> missingIDs;

void insertInToolList(Tool tl);

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
        Tool tl = Tool(argv[0], argv[1], atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
        missingIDs.push_back(tl);
    }else if(strcmp(cmdtype, "MISSP") == 0){
        Tool tool = Tool(argv[0], argv[1], atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
        insertInToolList(tool);
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

void insertInToolList(Tool tl) {
    auto itID = missingIDs.begin();
    if(missingIDs.size() == 0){
        missingIDs.push_back(tl);
        return;
    }

    int i;
    for(i = 0; i < missingIDs.size(); i++){
        if(missingIDs[i].getPriority() < tl.getPriority()) {
            itID++;
        }else
            break;
    }
    missingIDs.insert(itID, tl);
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

vector<Tool> getMissingIDVec(){
    vector<Tool> idxs = missingIDs;
    missingIDs.clear();
    return idxs;
}

vector<string> getNewIDVec(){
    vector<string> idxs = newIDs;
    newIDs.clear();
    return idxs;
}

