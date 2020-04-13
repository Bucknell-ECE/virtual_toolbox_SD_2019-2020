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
     * The date the tool was registered in the toolbox.
     */
    string registerDate;
    /**
     * The priority given to this specific tool.
     */
    int priority;

public:
    /**
     * Creates an instance of a tool object which holds the following info for a
     * unique tool.
     *
     * @param toolName the name of the tool
     * @param toolID the id of the tool
     * @param registerDate the registration date of the tool
     * @param priority the priority given to the tool for display
     */
    Tool(string toolName, string toolID, string registerDate, int priority);

    /** Getters and Setters */

    const string &getToolName() const;

    void setToolName(const string &toolName);

    const string &getToolId() const;

    void setToolId(const string &toolId);

    const string &getRegisterDate() const;

    void setRegisterDate(const string &registerDate);

    int getPriority() const;

    void setPriority(int priority);
};


#endif //VIRTUAL_TOOLBOX_SD_2019_2020_TOOL_H
