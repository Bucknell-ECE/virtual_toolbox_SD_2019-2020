//
// Created by MattTurconi on 2/5/2020.
//

#include <iostream>
#include <random>
#include "SQLiteDatabase.h"
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

vector<int> getUniqueRandIDs(int hi, int lo, int count){
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

vector<int> getMissingIDListTester(vector<int> missingIDs, int dbSize){
    vector<int> vec;
    int i, j;
    for(i = 0; i < dbSize; i++){
        int k = 0;
        for(j = 0; j < missingIDs.size(); j++){
            if(missingIDs[j] == (i + 100000000)){
                k = 1;
            }
        }
        if(k == 0){
            vec.push_back(i + 100000000);
        }
    }
    return vec;
}

void runMissingToolTest(int numMissing, int dbSize, int trials, SQLiteDatabase* db){
    srand(time(NULL));
    printf("Running Missing Test with %d tools, %d trials,"
           " %d missing tools\n", dbSize, trials, numMissing);
    int i;
    vector<int> missingIDs;
    vector<int> idList;
    vector<int> retMissingIDs;
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

int main(int argc, char * argv[]) {
    int dbsize = 10000;
    ToolScanner* tl = new ToolScanner();
    SQLiteDatabase* db = new SQLiteDatabase("test_databases/ToolBox" + to_string(dbsize) + ".db", tl);

    runMissingToolTest(15,dbsize, 10, db);


//    vector<int> missing = getUniqueRandIDs(300, 0, 10);
//    vector<int> lst = getMissingIDListTester(missing, 300);
//    printVec(missing);
//    db->findMissingTool(lst);
//
//    cout<<"MISSING RETURNED"<<endl;
//    vector<int> ret = db->getMissingIDs();
//    printVec(ret);
//    cout<<"Check Resp: " << checkMissingIDs(missing,ret) << endl;
}

