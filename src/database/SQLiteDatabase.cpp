//
// Created by MattTurconi on 2/5/2020.
//

#include <iostream>
#include "SQLiteDatabase.h"
#include "CallbackFunctions.h"
#include <string.h>
#include <ctime>

SQLiteDatabase::SQLiteDatabase(std::string dbName){
    this->dbName = dbName;
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
                              "ID INT PRIMARY KEY,"
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
void SQLiteDatabase::addTool(int ID, string toolName) {
    time_t now = time(0);
    string curDate = ctime(&now);
    curDate = curDate.substr(0,curDate.size() - 1);
    string cmd = "INSERT INTO TOOLS (ID, NAME, REG_DATE) VALUES"
                 "(" + to_string(ID) + ", '" + toolName + "', '" + curDate + "');";
    char* errMsg;
    sqlite3_exec(db, (const char*) cmd.c_str(), callback, (void*)"INS", &errMsg);
    cout<<errMsg<<endl;
}

//Done...
void SQLiteDatabase::findMissingTool(vector<int> toolIDs) {
    //Build list of ID's to pass to the select command
    string idList = "(";
    int i;
    for(i = 0; i < toolIDs.size(); i++){
        if(i == toolIDs.size() - 1)
            idList += to_string(toolIDs[i]) + ")";
        else
            idList += to_string(toolIDs[i]) + ", ";
    }
    //Build command
    string cmd = "SELECT * FROM TOOLS WHERE ID NOT IN " + idList + ";";
    char* errMsg;
    cout << cmd << endl;
    sqlite3_exec(db, (const char*) cmd.c_str(), callback, (void*)"MISS", &errMsg);
    //Get response
    string resp = getCallBackResponse();
    cout<<resp<<endl;
}

//Done
void SQLiteDatabase::dumpDB() {
    char* errMsg;
    const char* cmd = "SELECT * FROM TOOLS;";
    sqlite3_exec(db, cmd, callback, (void*) "DUMP", & errMsg);
    getCallBackResponse();
}


//As of right now I'm not sure why I would need this but I'm gonna keep it just in case
int SQLiteDatabase::selectData(vector<string> columns, string table) {
    //Need to format the string to send to the exec function
    string str = "SELECT ";
    char* errMsg;
    int i;
    for(i = 0; i < columns.size(); i ++){
        if(i == columns.size() - 1)
            str += columns[i] + " ";
        else
            str += columns[i] + ", ";
    }
    str += "FROM " + table + ";";
    const char* cmd = str.c_str();
    sqlite3_exec(db, cmd, callback, (void*) "SELECT", & errMsg);
    return 0;
}