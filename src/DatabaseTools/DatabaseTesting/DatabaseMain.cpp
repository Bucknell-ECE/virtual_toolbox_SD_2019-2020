//
// Created by MattTurconi on 2/22/2020.
//

#include "../SQLiteDatabase.h"
#include <iostream>
#include <random>
#include <ctime>

using namespace std;

//string filepath = "./../../../dbFiles/test_databases/";
string filepath = "C:\\Users\\MattTurconi\\virtual_toolbox_SD_2019-2020\\dbFiles\\test_databases\\";
int id_offset = 100000000;


/**
 * Creates a database of a specific size with string IDs
 *
 * @param size
 * @param dbName
 */
void createDatabaseOfSize(int size, string dbName){
    string dbPath = filepath + dbName;
    ToolScanner* tl = new ToolScanner();
    SQLiteDatabase* db_tools = new SQLiteDatabase(dbPath, tl);
    srand(time(NULL));

    int interval = size / 10;
    cout<<"Creating db of size " + to_string(size) << endl;
    int i, pri;
    for(i=0;i<size;i++){
        pri = 1 + (rand() % (5 - 1 + 1));
        db_tools->addTool(to_string(i + id_offset), "Tool" + to_string(i), pri);
        if(i % interval == 0)
            cout<<"Added " + to_string(i) + " so far."<<endl;
    }
}

/***
 * Gets a list of random String IDs with a specific count
 *
 * @param hi
 * @param lo
 * @param count
 * @return
 */
vector<string> getUniqueRandIDs(int hi, int lo, int count){
    srand(time(NULL));
    vector<string> str_ids;
    vector<int> int_ids;
    hi --;
    if(hi - lo < count)
        return str_ids;

    int i = 0;
    int j;
    int val;
    while(i < count){
        int k = 0;
        val = lo + (rand() % (hi - lo + 1));
        for(j = 0; j<str_ids.size(); j++){
            if(stoi(str_ids[j]) == val + id_offset){
                k = 1;
            }
        }
        if(k == 0) {
            str_ids.push_back(to_string(val + id_offset));
            i++;
        }
    }
    return str_ids;
}

/**
 * Given a list of missing IDs and a db size it will get rid of all the missing ids
 * from a list of all IDs.
 *
 * @param missingIDs
 * @param dbSize
 * @return
 */
vector<string> getMissingIDListTester(vector<string> missingIDs, int dbSize){
    vector<string> vec;
    int i, j;
    for(i = 0; i < dbSize; i++){
        int k = 0;
        for(j = 0; j < missingIDs.size(); j++){
            if(missingIDs[j] == to_string(i + id_offset)){
                k = 1;
            }
        }
        if(k == 0){
            vec.push_back(to_string(i + id_offset));
        }
    }
    return vec;
}

void printVec(vector<string> vec){
    int i;
    for(i=0;i<vec.size();i++)
        cout<< vec[i] << ",";
    cout<<endl;
}

void printVec(vector<Tool> vec){
    int i;
    for(i=0;i<vec.size();i++)
        cout<< vec[i].getToolId() << ",";
    cout<<endl;
}


int main(int argc, char* argv[]){
    //createDatabaseOfSize(20, "PrioDB20.db");

    ToolScanner* tl = new ToolScanner();
    SQLiteDatabase* db = new SQLiteDatabase(filepath + "PrioDB20.db", tl);

    db->dumpDB();
    vector<string> ids = getUniqueRandIDs(19, 0, 15);
    db->findMissingTool(1, ids);
    printVec(db->getToolVec());
    return 0;
}
