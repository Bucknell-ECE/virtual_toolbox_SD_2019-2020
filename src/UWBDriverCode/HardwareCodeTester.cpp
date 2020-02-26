//
// Created by MattTurconi on 2/5/2020.
// Edited by Owen Meng on 02/25/2020
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
int main(int argc, char *argv[]) {
    ToolScanner ts = ToolScanner();
    
    vector<string> input = ts.scanForTools();
    
    std::cout << "Tools in truck: \n";
        
    for (auto & value : input)
    {
        std::cout << value << " \n";
    }
}
