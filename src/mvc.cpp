// mvc.cpp
#include <iostream>
#include <unistd.h>
#include <QString>
#include <QStringList>
#include <unistd.h>
#include <string>
#include <QTest>
#include <QElapsedTimer>
#include <QtSql>
#include <stdio.h>
#include <wiringPi.h>
using namespace std;
#include <QtWidgets>
#include "FrontEnd/missing_model.h"
#include "FrontEnd/mainwidget.h"
#include "FrontEnd/registerwidget.h"
#include "DatabaseTools/SQLiteDatabase.h"
#include "UWBDriverCode/ToolScanner.h"


/**
 *
 * Tool names are as follows Wrench(and a number 1-500)
 * Tool Ids are a string that range between 100000000-100000500 
 * 
 */
string databaseFilepath = "../dbFiles/ToolBox400.db";

int main(int argc, char *argv[])
{
    
    Missing_Model model;
    
    QApplication app(argc, argv);

    QWidget window;
    window.resize(600, 300);
    window.setWindowTitle
          (QApplication::translate("childwidget", "Child widget"));
    window.show();

    vector<string> missing;
    QStringList output;
    
    
    MissingWidget *widget = new MissingWidget(&window);
    widget->show();

    RegisterWidget *regwidget = new RegisterWidget(&window);
    regwidget->move(400, 150);
    regwidget->show();
    
    //DB init
    cout<<"Booting\n"<<endl;
    ToolScanner* tl = new ToolScanner();
    cout<<"Complete\n"<<endl;
    SQLiteDatabase* db_tools = new SQLiteDatabase(databaseFilepath, tl);
    
    
    
    db_tools->addTool(to_string(22319), "Tag F5");
    db_tools->addTool(to_string(52885), "Tag T2");
    db_tools->addTool(to_string(140), "Tag T1");
    db_tools->addTool(to_string(53644), "Tag T3");
    db_tools->addTool(to_string(309), "Tag T4");
    
     
    /**
     * Everything in here should be in limit switch loop
     */

        const int button = 27;
         wiringPiSetup();
        //set gpio pin 26(25) to high 3.3V and gpio 16(27) to output
        pinMode(25,OUTPUT);
        digitalWrite(25,1);
        pinMode(button,INPUT);
        bool flag = false;
        
        
        
      
        
        
        int lastButtonRead = LOW;
        int thisButtonRead = LOW;
        bool buttonLowToHigh = false;
        while(1){
            lastButtonRead = thisButtonRead;
            thisButtonRead = digitalRead(button);
            if ((thisButtonRead == HIGH)&&(lastButtonRead==LOW)) {
                buttonLowToHigh = true;
            } else {
                buttonLowToHigh = false;
            }
            
            if (buttonLowToHigh == false){
                //flag = true;
                //delay(50);
                //cout<<"Test 1" <<endl;
            }
            if (buttonLowToHigh == true){
                
                //Gets the missing tools
                missing = db_tools->getMissingToolIDs();
                cout<<"Test " <<endl;
    
                //Converts into UI string object
                for (int i = 0; i < missing.size(); i++){
                    QString next = QString::fromStdString(missing[i]);
                    cout << missing[i] << "\n";
                    output.append(next);
                }

                //all that is needed for reloading data
                widget->SetData(output);
                widget->loadView();
    
                
                flag = false;
                //For widget
                return app.exec();
            }
        }
        //No widget
        //return app.exec();
        return 0;
}
