//
// Created by MattTurconi on 2/5/2020.
//

#ifndef VIRTUAL_TOOLBOX_SD_2019_2020_SQLITEDATABASE_H
#define VIRTUAL_TOOLBOX_SD_2019_2020_SQLITEDATABASE_H

#define ONE_HOUR_SEC 3600
#include "../../sqlite3/sqlite3.h"
#include <vector>
#include <string>
#include "../HardwareSkeletonCode/ToolScanner.h"
#include "Tool.h"

/**
 * This value sets lowest priority that a tool can receive,
 * this is also the value specified if no priority is given
 * during tool registration.
 */
#define LOWEST_PRIORITY_VAL 5

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
    string dbPath;

    /**
     * List of missing tools as Tool Objects
     */
    vector<Tool> missingTools;

    /**
     * List of new tool IDs
     */
    vector<string> newIDs;

    /**
     * Called by the findMissingTool function in order to update
     * the miss_count field and last_miss_date field in the database
     * for any missing tool.
     *
     * This function will only update the miss_count and last_miss_date field if
     * the current time is one hour greater than the last time it was was reported missing.
     * The time is checked in order to eliminate the system from over-counting the number
     * of times the tool is recorded missing, as a use-case exists where more than on
     * scan for missing tools could be made during one singular use of the user.
     */
    void updateMissingToolCount();

public:
    /**
     * Creates/opens a Database Tools given a filepath for the database.
     * Requires a ToolScanner object that will allow for the database
     * to receive Tool ID's from the toolbox.
     *
     * If a database that is provided in the dbFilePath parameter, a db
     * file will be created. The function creates a SQL style database with
     * one table named TOOLS with the following fields:
     * ID TEXT (primary key) - the id of the tool as a string
     * NAME TEXT - the human readable name of the tool
     * REG_DATE INT - the date the tool was registered as a time_t value
     * PRIORITY INT - the priority of the tool used to display the tool to the user
     * MISS_COUNT INT - the number of times that the tool has been recorded missing
     * LAST_MISS_DATE INT - the last date and time the tool has been recorded missing as a time_t value
     *
     * @param dbFilePath path of a Database Tools .db file
     * @param toolScanner a ToolScanner object for a physical scanner
     */
    SQLiteDatabase(string dbFilePath, ToolScanner* toolScanner);

    /**
     * Adds a tool to the Database Tools with a new tool ID and
     * the human readable name of the tool.
     * The priority works as follows:
     * 1 - Highest priority
     * LOWEST_PRIORITY_VAL - Lowest priority
     *
     * @param tooID an unique tool id integer
     * @param toolName a human readable tool name string.
     * @param priority an integer between 1 and LOWEST_PRIORITY_VAL inclusive
     */
    void addTool(string ID, string toolName, int priority = LOWEST_PRIORITY_VAL);

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
     * @param sorted field to indicate if the missing tool list should be sorted by priority. 1 Yes, 0 No
     * @param retColField an optional string identifier
     * @param toolIDs an optional list of tool IDs
     */
    void findMissingTool(int sorted, vector<string> toolIDs = {});

    /**
     * Dumps the whole database to the terminal
     * WARNING
     * Do not use outside of small scale testing
     */
    void dumpDB();

    /**
     * Updates the priority of a given tool based on its tool_id
     *
     * @param tool_id the id for a given tool
     * @param priority the new priority integer to give the tool
     */
    void update_priority(string tool_id, int priority);

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
     * If a ToolScanner object is not provided the ToolScanner object that was provided
     * at object creation will be used
     *
     * @param toolIDs an optional list of tool IDs
     */
    vector<string> findNewTool(ToolScanner* ts = nullptr, vector<string> toolIDs = {});

    /**
     * Registers a tool given a tool name string
     *
     * @param toolName the name of the tool
     * @param ts an optional tool scanner object to get the list of toolIds from
     * @return a 1 on success and a 0 on error
     */
    int registerNewTool(string toolName, ToolScanner* ts = nullptr);

    /**
     * Calls the find missing tool function and returns a list of tool names that are missing
     *
     * @return A vector of Tool objects
     */
    vector<Tool> getMissingTools();

    /**
     * Calls the find missing tool function and returns a list of missing tool names that are
     * int the return vector by priority.
     *
     * @return A vector of Tool objects sorted by priority number
     */
    vector<Tool> getMissingToolsSorted();

    /**
     * A getter method for the list of new string ids after a findNewTools call
     *
     * @return A vector of new string ids
     */
    vector<string> getNewIDs();

    /**
     * Getter for the sqlite3 database.
     * Used primarily as a way to debug small databases in a development setting.
     *
     * Dumps entire database to standard output
     */
     sqlite3* get_db();

     vector<Tool> getToolVec(){
         return missingTools;
     }
};

//TODO Track number of times it was detected out of box.
// Will incorporate the last Physical time it was checked out
// Is the tool checked out flag

#endif //VIRTUAL_TOOLBOX_SD_2019_2020_SQLITEDATABASE_H
