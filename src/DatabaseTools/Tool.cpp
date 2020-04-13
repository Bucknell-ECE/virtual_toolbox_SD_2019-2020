//
// Created by MattTurconi on 4/12/2020.
//

#include "Tool.h"

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

const string &Tool::getRegisterDate() const {
    return registerDate;
}

void Tool::setRegisterDate(const string &registerDate) {
    Tool::registerDate = registerDate;
}

int Tool::getPriority() const {
    return priority;
}

void Tool::setPriority(int priority) {
    Tool::priority = priority;
}

Tool::Tool(string toolName, string toolID, string registerDate, int priority) {
    this->toolName = toolName;
    this->toolID = toolID;
    this->registerDate = registerDate;
    this->priority = priority;
}
