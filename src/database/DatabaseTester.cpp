//
// Created by MattTurconi on 2/5/2020.
//

#include <iostream>
#include "SQLiteDatabase.h"

int main(int argc, char * argv[]) {
    SQLiteDatabase *db_tools = new SQLiteDatabase("../../ToolBox.db");
    vector<int> x = {12323, 123456, 233456, 357345, 3451123, 52443, 128382};
    db_tools->findMissingTool(x);

    return 1;
}