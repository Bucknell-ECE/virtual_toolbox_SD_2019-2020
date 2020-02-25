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
using namespace std;
#include <QtWidgets>
#include "FrontEnd/missing_model.h"
#include "FrontEnd/mainwidget.h"
#include "FrontEnd/registerwidget.h"
#include "DatabaseTools/SQLiteDatabase.h"
#include "HardwareSkeletonCode/ToolScanner.h"


/**
 *
 * Tool names are as follows Wrench(and a number 1-500)
 * Tool Ids are a string that range between 100000000-100000500 
 * 
 */
string databaseFilepath = "../dbFiles/ToolBox500.db";

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
    ToolScanner* tl = new ToolScanner();
    SQLiteDatabase* db_tools = new SQLiteDatabase(databaseFilepath, tl);

    /**
     * Everything in here should be in some loop
     */
    //Gets the missing tools
    missing = db_tools->getMissingToolIDs();
    
    //Converts into UI string object
    for (int i = 0; i < missing.size(); i++){
        QString next = QString::fromStdString(missing[i]);
        output.append(next);
    }

    //all that is needed for reloading data
    widget->SetData(output);
    widget->loadView();
    
    return app.exec();
 

}
