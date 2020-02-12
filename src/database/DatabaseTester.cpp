//
// Created by MattTurconi on 2/5/2020.
//

#include <iostream>
#include "SQLiteDatabase.h"

int main(int argc, char * argv[]) {
    SQLiteDatabase *db_tools = new SQLiteDatabase(
            "C:/Users/MattTurconi/virtual_toolbox_SD_2019-2020/ToolBox.db");


//    db_tools->addTool(12554455, "WRENCH1");
//    db_tools->addTool(52464455, "WRENCH2");
//    db_tools->addTool(12665455, "WRENCH3");
//    db_tools->addTool(12666555, "WRENCH4");
   db_tools->findMissingTool({52464455,12666555,12665455});

    return 1;
}