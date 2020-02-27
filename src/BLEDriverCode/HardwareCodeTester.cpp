//
// Created by MattTurconi on 2/5/2020.
//

#include "ToolScanner.h"

/**
 * This is where you can run all your test code from.
 * Define all your variables and try out the functions here.
 *
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[]){
    ToolScanner ts = ToolScanner();
}//
// Created by MattTurconi on 2/5/2020.
//

#include "ToolScanner.h"
#include <iostream>

/**
 * This is where you can run all your test code from.
 * Define all your variables and try out the functions here.
 *
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[]){
    ToolScanner ts = ToolScanner();
    vector<string> test = ts.scanForTools();
    for (vector<string>::const_iterator i = test.begin(); i!=test.end(); ++i){
        std::cout << (*i) << ' ';
    }
}
