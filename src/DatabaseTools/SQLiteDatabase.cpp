//
// Created by MattTurconi on 2/5/2020.
//

#include <iostream>
#include "SQLiteDatabase.h"
#include "CallbackFunctions.h"
#include <ctime>

SQLiteDatabase::SQLiteDatabase(std::string dbName, ToolScanner* toolScanner){
    this->dbName = dbName;
    this->toolScanner = toolScanner;
    //Check if the DB exists, if not create it and set up table
    if(sqlite3_open(dbName.c_str(), & db)){
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
                              "REG_DATE TEXT NOT NULL);";
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

//Done...
void SQLiteDatabase::addTool(string ID, string toolName) {
    time_t now = time(0);
    string curDate = ctime(&now);
    curDate = curDate.substr(0,curDate.size() - 1);
    string cmd = "INSERT INTO TOOLS (ID, NAME, REG_DATE) VALUES"
                 "(" + ID + ", '" + toolName + "', '" + curDate + "');";
    char* errMsg;
    sqlite3_exec(db, (const char*) cmd.c_str(), callback, (void*)"INS", &errMsg);
}

//Done...
void SQLiteDatabase::findMissingTool(vector<string> toolIDs) {
    //If no list was provided we need to get it from teh scanner
    if(toolIDs.size() == 0)
        toolIDs = toolScanner->scanForTools();
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

    string cmd = "SELECT * FROM TOOLS WHERE ID NOT IN " + idList + ";";    
    cout << "CMD" << endl;
    char* errMsg;
    int rv = sqlite3_exec(db, (const char*) cmd.c_str(), callback, (void*)"MISS", &errMsg);
    //Get response
    cout << rv << endl;
    if (rv)
        cout << errMsg << endl;
    cout << "END" << endl;
    missingIDs = getMissingIDVec();
}

/**
 * WITH ids (ID) AS (VALUES (12554455), (2252252), (52464455), (12665455), (12666555))
 * SELECT * FROM ids WHERE ID NOT IN ( SELECT ID FROM TOOLS );
 * @param toolIDs
 * @return
 */
 //Done
void SQLiteDatabase::findNewTool(vector<string> toolIDs){
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
}

//Done
void SQLiteDatabase::dumpDB() {
    char* errMsg;
    const char* cmd = "SELECT * FROM TOOLS;";
    sqlite3_exec(db, cmd, callback, (void*) "DUMP", & errMsg);
    getCallBackResponse();
}

void SQLiteDatabase::deleteToolByID(string id) {
    string cmd = "DELETE FROM TOOLS WHERE ID=" + id;
    char* errMsg;
    sqlite3_exec(db, (const char*) cmd.c_str(), callback, (void *)"DELETE", &errMsg);
}

//As of right now I'm not sure why I would need this but I'm gonna keep it just in case
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

vector<string> SQLiteDatabase::getMissingIDs() {
    cout << "missing tool" << endl;
    findMissingTool();
    return missingIDs;
}

vector<string> SQLiteDatabase::getNewIDs() {
    findNewTool();
    return newIDs;
}
