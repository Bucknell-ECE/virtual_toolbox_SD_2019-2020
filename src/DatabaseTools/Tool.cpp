//
// Created by MattTurconi on 4/12/2020.
//

#include "Tool.h"

Tool::Tool(string toolID, string toolName, int registerDate, int priority, int miss_count, int last_miss_date){
    this->toolID = toolID;
    this->toolName = toolName;
    this->registerDate = registerDate;
    this->priority = priority;
    this->miss_count = miss_count;
    this->last_miss_date = last_miss_date;
}

const string &Tool::getToolName() const {
    return toolName;
}

void Tool::setToolName(const string &toolName) {
    Tool::toolName = toolName;
}

const string &Tool::getToolId() const {
    return toolID;
}

void Tool::setToolId(const string &toolId) {
    toolID = toolId;
}

int Tool::getRegisterDate() const {
    return registerDate;
}

void Tool::setRegisterDate(int registerDate) {
    Tool::registerDate = registerDate;
}

int Tool::getPriority() const {
    return priority;
}

void Tool::setPriority(int priority) {
    Tool::priority = priority;
}

int Tool::getMissCount() const {
    return miss_count;
}

void Tool::setMissCount(int missCount) {
    miss_count = missCount;
}

int Tool::getLastMissDate() const {
    return last_miss_date;
}

void Tool::setLastMissDate(int lastMissDate) {
    last_miss_date = lastMissDate;
}


