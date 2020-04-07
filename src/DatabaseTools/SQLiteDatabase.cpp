//
// Created by MattTurconi on 2/5/2020.
//

#include <iostream>
#include "SQLiteDatabase.h"
#include "CallbackFunctions.h"
#include <ctime>

SQLiteDatabase::SQLiteDatabase(std::string dbFilePath, ToolScanner* toolScanner){
    this->dbPath = dbFilePath;
    this->toolScanner = toolScanner;
    //Check if the DB exists, if not create it and set up table
    if(sqlite3_open(dbFilePath.c_str(), & db)){
        //TODO throw an error here
        cout << sqlite3_errmsg(db) << endl;
    }else{
        //Check if the TOOLS table exists
        char* errMsg;
        const char* exist_msg = "select count(type) from sqlite_master "
                                "where type='table' and name='TOOLS';";
        sqlite3_exec(db, exist_msg, callback, (void*)"EXIST", & errMsg);

        //If it does not the callback response will be 0
        if(getCallBackResponse() == "0"){
            //Make a new table in the db
            const char* cmd = "CREATE TABLE TOOLS("
                              "ID TEXT PRIMARY KEY,"
                              "NAME TEXT NOT NULL,"
                              "REG_DATE TEXT NOT NULL,"
                              "PRIORITY INT NOT NULL);";
            sqlite3_exec(db, cmd, callback, (void*)"CREATE", & errMsg);
        }
    }
}

void SQLiteDatabase::operator delete(void *ptr) {
    SQLiteDatabase* pt = (SQLiteDatabase*) ptr;
    sqlite3_close(pt->get_db());
    free(ptr);
}

sqlite3* SQLiteDatabase::get_db(){
    return this->db;
}

void SQLiteDatabase::addTool(string ID, string toolName, int priority) {
    time_t now = time(0);
    string curDate = ctime(&now);
    curDate = curDate.substr(0,curDate.size() - 1);
    string cmd = "INSERT INTO TOOLS (ID, NAME, REG_DATE, PRIORITY) VALUES"
                 "(" + ID + ", '" + toolName + "', '" + curDate + "', " +
                 to_string(priority) + ");";
    char* errMsg;
    int rv = sqlite3_exec(db, (const char*) cmd.c_str(), callback, (void*)"INS", &errMsg);
    //Get response
    if (rv)
        cout << errMsg << endl;
}

void SQLiteDatabase::update_priority(string tool_id, int priority){
    string cmd = "UPDATE TOOLS SET PRIORITY = " + to_string(priority) + " WHERE (ID == " + tool_id + ");";

    char* errMsg;
    int rv = sqlite3_exec(db, (const char*) cmd.c_str(), callback, (void*)"UPDATE", &errMsg);
    if(rv)
        cout << errMsg << endl;
}

void SQLiteDatabase::findMissingTool(int sorted, string retColField, vector<string> toolIDs) {
    //If no list was provided we need to get it from teh scanner
    if(toolIDs.size() == 0)
        toolIDs = toolScanner->scanForTools();

    string cmd_flag;
    if(sorted)
        cmd_flag = "MISSP"; //Flag that sorts the missing tools in the return vector
    else
        cmd_flag = "MISS";

    if(retColField == "")
        retColField = "ID";
    retColField += ", PRIORITY";
    //Build list of ID's to pass to the select command
    string idList = "( VALUES";
    int i;
    for(i = 0; i < toolIDs.size(); i++){
        if(i == toolIDs.size() - 1)
            idList += "(" + toolIDs[i] + "))";
        else
            idList += "(" + toolIDs[i] + "), ";
    }
    //Build command

    string cmd = "SELECT " + retColField + " FROM TOOLS WHERE ID NOT IN " + idList + ";";
    char* errMsg;
//    cout << "CMD" << endl;
//    cout << cmd << endl;
    int rv = sqlite3_exec(db, (const char*) cmd.c_str(), callback, (void*)cmd_flag.c_str(), &errMsg);
    //Get response
    if (rv)
        cout << errMsg << endl;
    getPriorityVec();
    missingIDs = getMissingIDVec();
}

vector<string> SQLiteDatabase::findNewTool(ToolScanner* ts, vector<string> toolIDs){
    //If no tool list is provided we need to get it from the user.
    if(toolIDs.size() == 0)
        toolIDs = toolScanner->scanForTools();

    //Build the values list
    string valueList = "(VALUES ";
    int i;
    for(i=0; i<toolIDs.size(); i++){
        if(i == toolIDs.size() - 1)
            valueList += "(" + toolIDs[i] + ")) ";
        else
            valueList += "(" + toolIDs[i] + "), ";
    }
    //Build the sql command
    string cmd = "WITH ids (ID) AS ";
    cmd += valueList;
    cmd += "SELECT * FROM ids WHERE ID NOT IN ( SELECT ID FROM TOOLS );";

    //Call the command
    char* errMsg;
    int rc = sqlite3_exec(db, (const char*) cmd.c_str(), callback, (void *)"NEW", & errMsg);

    vector<string> idxs = getNewIDVec();
    newIDs = idxs;
    return newIDs;
}

int SQLiteDatabase::registerNewTool(string toolName, ToolScanner *tls) {
    vector<string> ids;
    if(tls == nullptr)
        ids = findNewTool();
    else
        ids = findNewTool(tls);

    if(ids.size() == 1)
        addTool(toolName,ids[0]);
    else
        return 0;
}

void SQLiteDatabase::dumpDB() {
    char* errMsg;
    const char* cmd = "SELECT * FROM TOOLS;";
    int rv = sqlite3_exec(db, cmd, callback, (void*) "DUMP", & errMsg);
    //Get response
    if (rv)
        cout << errMsg << endl;
    getCallBackResponse();
}

void SQLiteDatabase::deleteToolByID(string id) {
    string cmd = "DELETE FROM TOOLS WHERE ID=" + id;
    char* errMsg;
    sqlite3_exec(db, (const char*) cmd.c_str(), callback, (void *)"DELETE", &errMsg);
}

string SQLiteDatabase::selectToolByID(string toolID, string table) {
    string str = "SELECT * ";
    char* errMsg;
    str += "FROM " + table + " WHERE ID = " + toolID + ";";
    const char* cmd = str.c_str();
    sqlite3_exec(db, cmd, callback, (void*) "SELECT", & errMsg);
    return getSelectResponse();
}

string SQLiteDatabase::selectToolByName(string toolName, string table) {
    string str = "SELECT * ";
    char* errMsg;
    str += "FROM " + table + " WHERE NAME = '" + toolName + "';";
    const char* cmd = str.c_str();
    sqlite3_exec(db, cmd, callback, (void*) "SELECT", & errMsg);
    return getSelectResponse();
}

vector<string> SQLiteDatabase::getNewIDs() {
    return newIDs;
}

vector<string> SQLiteDatabase::getMissingToolIDs() {
    findMissingTool(0);
    return missingIDs;
}

vector<string> SQLiteDatabase::getMissingToolNames() {
     findMissingTool(0, "NAME");
     return missingIDs;
}

vector<string> SQLiteDatabase::getMissingToolIDsSorted() {
    findMissingTool(1);
    return missingIDs;
}

vector<string> SQLiteDatabase::getMissingToolNamesSorted() {
    findMissingTool(1, "NAME");
    return missingIDs;
}

vector<string> SQLiteDatabase::get_missing_ids_vec() {
    return missingIDs;
}
