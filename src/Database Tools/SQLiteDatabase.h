//
// Created by MattTurconi on 2/5/2020.
//

#ifndef VIRTUAL_TOOLBOX_SD_2019_2020_SQLITEDATABASE_H
#define VIRTUAL_TOOLBOX_SD_2019_2020_SQLITEDATABASE_H

#include "../../sqlite3/sqlite3.h"
#include <vector>
#include <string>
#include "../HardwareSkeletonCode/ToolScanner.h"

using namespace std;

class SQLiteDatabase {
private:
    /**
     * A pointer to the sqlite3 database interface
     */
    sqlite3 *db;

    /**
     * Tool scanner object that will allow us to get info about
     * the tool tag IDs in the toolbox
     */
     ToolScanner* toolScanner;

    /**
     * File path name of the database
     */
    string dbName;

    /**
     * List of missing tool IDs
     */
    vector<string> missingIDs;

    /**
     * List of new tool IDs
     */
    vector<string> newIDs;

public:
    /**
     * Creates/opens a Database Tools depending on the name of the
     * Database Tools file name.
     *
     * @param dbName name of a Database Tools .db file
     */
    SQLiteDatabase(string dbName, ToolScanner* toolScanner);

    /**
     * Adds a tool to the Database Tools with a new tool ID and
     * the human readable name of the tool.
     *
     * @param tooID an unique tool id integer
     * @param toolName a human readable tool name string.
     */
    void addTool(string ID, string toolName);

    /**
     * Closes the database and frees the memory
     *
     * @param ptr object to free
     */
    void operator delete(void *ptr);

    /**
     * Selects all the columns for a tool based on the tool ID string
     *
     * @param toolID a string representing an ID for a tool
     * @param table The table we want to select data from
     * @return the resulting columns from the database
     */
    string selectToolByID(string toolID, string table = "TOOLS");

    /**
     * Selects all the columns for a tool based on the tool name string
     *
     * @param toolName the name of the tool as a string
     * @param table the name of the table we want to select data from
     * @return the resulting columns from the database
     */
    string selectToolByName(string toolName, string table = "TOOLS");

    /**
     * Finds the missing tools from a list provided by the tool scanner object
     *
     * If a list of tools are not provided, a list will be requested from the tool
     * scanner object
     *
     * @param toolIDs an optional list of tool IDs
     */
    void findMissingTool(vector<string> toolIDs = {});

    /**
     * Dumps the whole database to the terminal
     * WARNING
     * Do not use outside of small scale testing
     */
    void dumpDB();

    /**
     * Deletes a tool in the database by the tool id string
     *
     * @param id
     */
    void deleteToolByID(string id);

    /**
     * Finds a new tool in the toolbox
     *
     * If a list of tools are not provided, a list will be requested from the tool
     * scanner object
     *
     * @param toolIDs an optional list of tool IDs
     */
    void findNewTool(vector<string> toolIDs = {});

    /**
     * Calls the find missing tool function and returns a list of string ids
     *
     * @return A vector of string ids
     */
    vector<string> getMissingIDs();

    /**
     * Calls the find ne tool function and returns a list of new string ids
     *
     * @return A vector of new string ids
     */
    vector<string> getNewIDs();

    /**
     * Getter for the sqlite3 database
     */
     sqlite3* get_db();

};


#endif //VIRTUAL_TOOLBOX_SD_2019_2020_SQLITEDATABASE_H
