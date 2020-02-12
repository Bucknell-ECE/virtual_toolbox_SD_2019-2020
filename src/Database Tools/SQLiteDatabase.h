//
// Created by MattTurconi on 2/5/2020.
//

#ifndef VIRTUAL_TOOLBOX_SD_2019_2020_SQLITEDATABASE_H
#define VIRTUAL_TOOLBOX_SD_2019_2020_SQLITEDATABASE_H

#include "../../sqlite3/sqlite3.h"
#include <vector>
#include <string>

using namespace std;

class SQLiteDatabase {
private:
    //SQLite Database Tools object
    sqlite3 *db;

    //Database file
    string dbName;

public:
    /**
     * Creates/opens a Database Tools depending on the name of the
     * Database Tools file name.
     *
     * @param dbName name of a Database Tools .db file
     */
    SQLiteDatabase(string dbName);

    /**
     * Adds a tool to the Database Tools with a new tool ID and
     * the human readable name of the tool.
     *
     * @param tooID an unique tool id integer
     * @param toolName a human readable tool name string.
     */
    void addTool(int ID, string toolName);

    //TODO make sure we close the Database Tools and free the db pointer
    void operator delete(void *ptr);

    sqlite3* get_db();

    int selectData(vector<string> columns, string table = "TOOLS");

    void findMissingTool(vector<int> toolIDs);

    void dumpDB();

    int addTool(vector<string> columns, vector<string> values);

};


#endif //VIRTUAL_TOOLBOX_SD_2019_2020_SQLITEDATABASE_H