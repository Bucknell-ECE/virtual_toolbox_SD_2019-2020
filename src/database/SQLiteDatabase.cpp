//
// Created by MattTurconi on 2/5/2020.
//

#include <iostream>
#include "SQLiteDatabase.h"
#include "CallbackFunctions.h"

SQLiteDatabase::SQLiteDatabase(std::string dbName){
    this->dbName = dbName;
    if(sqlite3_open(dbName.c_str(), & db)){
        //TODO throw an error here
        cout << "ERROR" << endl;
    }else{
        //Do whatever else needs done
        cout << "SUCCESS" << endl;
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
    print_cols = 1;
    cout << print_cols << endl;
    sqlite3_exec(db, cmd, callback, (void*) "SELECT", & errMsg);
    return 0;
}

int SQLiteDatabase::addTool(vector<string> columns, vector<string>) {
    return 0;
}

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
    cout << idList << endl;
}



