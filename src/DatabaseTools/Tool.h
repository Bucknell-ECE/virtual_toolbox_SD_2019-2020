//
// Created by MattTurconi on 4/12/2020.
//

#ifndef VIRTUAL_TOOLBOX_SD_2019_2020_TOOL_H
#define VIRTUAL_TOOLBOX_SD_2019_2020_TOOL_H

#include <string>

using namespace std;

/**
 * An object that stores the data from the tool box database.
 */
class Tool {
private:
    /**
     * The name of the tool.
     */
    string toolName;
    /**
     * The identification number of the tool.
     */
    string toolID;
    /**
     * The date the tool was registered in the toolbox as an integer that
     * could be converted to time_t.
     */
    int registerDate;
    /**
     * The priority given to this specific tool.
     */
    int priority;
    /**
     * The number of times this tool was documented missing
     */
    int miss_count;
    /**
     * The last recorded date and time this tool was documented missing as an int
     * that could be converted to a time_t
     */
    int last_miss_date;

public:
    /**
     * Creates an instance of a tool object which holds the following info for a
     * unique tool.
     *
     * @param toolID the id of the tool
     * @param toolName the name of the tool
     * @param registerDate the registration date of the tool
     * @param priority the priority given to the tool for display
     * @param miss_count the number of times the tool has been missing
     * @param last_miss_date the last date the tool was missing
     */
    Tool(string toolID, string toolName, int registerDate, int priority, int miss_count, int last_miss_date);

    /** Getters and Setters */

    const string &getToolName() const;

    void setToolName(const string &toolName);

    const string &getToolId() const;

    void setToolId(const string &toolId);

    int getRegisterDate() const;

    void setRegisterDate(int registerDate);

    int getPriority() const;

    void setPriority(int priority);

    int getMissCount() const;

    void setMissCount(int missCount);

    int getLastMissDate() const;

    void setLastMissDate(int lastMissDate);
};


#endif //VIRTUAL_TOOLBOX_SD_2019_2020_TOOL_H
