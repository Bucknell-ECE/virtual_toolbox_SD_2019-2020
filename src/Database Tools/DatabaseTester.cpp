//
// Created by MattTurconi on 2/5/2020.
//

#include <iostream>
#include "SQLiteDatabase.h"

void createDatabaseOfSize(int size, string dbName){
    string dbPath = "C:/Users/MattTurconi/virtual_toolbox_SD_2019-2020/test_databases/" + dbName;
    ToolScanner* tl = new ToolScanner();
    SQLiteDatabase* db_tools = new SQLiteDatabase(dbPath, tl);

    int interval = size / 10;
    cout<<"Creating db of size " + to_string(size) << endl;
    int i;
    for(i=0;i<size;i++){
        db_tools->addTool(i + 100000000, "Tool" + to_string(i));
        if(i % interval == 0)
            cout<<"Added " + to_string(i) + " so far."<<endl;
    }
}
/**
 * To be run once so all test databases can be setup.
 */
void createAllTestDatabases(){
    createDatabaseOfSize(100, "ToolBox100.db");
    createDatabaseOfSize(300, "ToolBox300.db");
    createDatabaseOfSize(500, "ToolBox500.db");
    createDatabaseOfSize(1000, "ToolBox1000.db");
    createDatabaseOfSize(10000, "ToolBox10000.db");
}


int main(int argc, char * argv[]) {

}

