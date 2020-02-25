//
// Created by MattTurconi on 2/5/2020.
//

#include <iostream>
#include <random>
#include "../Database Tools/SQLiteDatabase.h"
#include <ctime>
#include <chrono>

int checkMissingIDs(vector<int> vec1, vector<int> vec2);
void printVec(vector<int> vec);

void createDatabaseOfSize(int size, string dbName){
    string dbPath = "test_databases/" + dbName;
    ToolScanner* tl = new ToolScanner();
    SQLiteDatabase* db_tools = new SQLiteDatabase(dbPath, tl);

    int interval = size / 10;
    cout<<"Creating db of size " + to_string(size) << endl;
    int i;
    for(i=0;i<size;i++){
        db_tools->addTool(to_string(i + 100000000), "Tool" + to_string(i));
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

vector<string> getUniqueRandIDs(int hi, int lo, int count){
    vector<int> ids;
    hi --;
    if(hi - lo < count)
        return ids;

    int i = 0;
    int j;
    int val;
    while(i < count){
        int k = 0;
        val = lo + (rand() % (hi - lo + 1));
        for(j = 0; j<ids.size(); j++){
            if(ids[j] == val + 100000000){
                k = 1;
            }
        }
        if(k == 0) {
            ids.push_back(val + 100000000);
            i++;
        }
    }
    return ids;
}

vector<string> getMissingIDListTester(vector<int> missingIDs, int dbSize){
    vector<string> vec;
    int i, j;
    for(i = 0; i < dbSize; i++){
        int k = 0;
        for(j = 0; j < missingIDs.size(); j++){
            if(missingIDs[j] == (i + 100000000)){
                k = 1;
            }
        }
        if(k == 0){
            vec.push_back(to_string(i + 100000000));
        }
    }
    return vec;
}

void runMissingToolTest(int numMissing, int dbSize, int trials, SQLiteDatabase* db){
    srand(time(NULL));
    printf("Running Missing Test with %d tools, %d trials,"
           " %d missing tools\n", dbSize, trials, numMissing);
    int i;
    vector<string> missingIDs;
    vector<string> idList;
    vector<string> retMissingIDs;
    double totTime = 0;

    for(i = 1; i <= trials; i++){
        missingIDs = getUniqueRandIDs(dbSize, 0, numMissing);
        idList = getMissingIDListTester(missingIDs, dbSize);

        auto start = chrono::high_resolution_clock::now();
        db->findMissingTool(idList);
        auto end = chrono::high_resolution_clock::now();

        double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;

        retMissingIDs = db->getMissingIDs();
        string valid = "True";
        int res = checkMissingIDs(retMissingIDs, missingIDs);
        if(res == 0) {
            printVec(missingIDs);
            printVec(retMissingIDs);
            valid = "False";
        }
        printf("Trial %d: %.6f secs\t Valid: %s\n", i, time_taken, valid.c_str());
	totTime += time_taken;
    }
    printf("Average time: %.6f\n", totTime / trials);

}

int checkMissingIDs(vector<int> vec1, vector<int> vec2) {
    if(vec1.size() != vec2.size()){
        return 0;
    }
    int i,j;
    for(i = 0; i<vec1.size(); i++){
        int found = 0;
        for(j = 0; j<vec2.size(); j++){
            if(vec1[i] == vec2[j])
                found = 1;
        }
        if(found == 0)
            return 0;
    }
    return 1;
}

void printVec(vector<int> vec){
    int i;
    for(i=0;i<vec.size();i++)
        cout<<to_string(vec[i]) << ",";
    cout<<endl;
}

void testNewTools(int dbSize, int trials, SQLiteDatabase* db, int numMissing = 0, int newIDCount = 1){
    vector<int> missing, lst, newIDs;
    double totTime = 0;
    int i;
    for(i = 1; i <= trials; i++) {
        //Get some missing ids if we want
        missing = getUniqueRandIDs(dbSize, 0, numMissing);
        //Get the list of IDs based on missing ids
        lst = getMissingIDListTester(missing, dbSize);
        //Now get some new ID's out of the range of the database
        newIDs = getUniqueRandIDs(dbSize + 100, dbSize, newIDCount);
        //Put new ID's on the list
        int j;
        for (j = 0; j < newIDs.size(); j++) {
            lst.push_back(newIDs[j]);
        }
        //Run query and get tools
        auto start = chrono::high_resolution_clock::now();
        db->findNewTool(lst);
        auto end = chrono::high_resolution_clock::now();

        //Compute time difference
        double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;
        totTime += time_taken;

        vector<int> retNewIDs = db->getNewIDs();
        string valid = "True";
        int res = checkMissingIDs(newIDs, retNewIDs);
        if(res == 0) {
            printVec(newIDs);
            printVec(retNewIDs);
            valid = "False";
        }
        printf("Trial %d: %.6f secs\t Valid: %s\n", i, time_taken, valid.c_str());
    }
    printf("Average time for %d Trials: %.6f\n", trials, totTime/trials);
}

int main(int argc, char * argv[]) {
    int dbsize = 10000;
    ToolScanner* tl = new ToolScanner();
    SQLiteDatabase* db = new SQLiteDatabase("test_databases/ToolBox" + to_string(dbsize) + ".db", tl);

    testNewTools(dbsize, 100, db);

    //runMissingToolTest(15, dbsize, 100, db);



//
//    cout<<"MISSING RETURNED"<<endl;
//    vector<int> ret = db->getMissingToolIDs();
//    printVec(ret);
//    cout<<"Check Resp: " << checkMissingIDs(missing,ret) << endl;
}

