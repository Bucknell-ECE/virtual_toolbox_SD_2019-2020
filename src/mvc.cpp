// mvc.cpp
#include <iostream>
#include <unistd.h>
#include <QString>
#include <QStringList>
#include <unistd.h>
#include <QTest>
#include <QElapsedTimer>
#include <QtSql>
using namespace std;
#include <QtWidgets>
#include "FrontEnd/missing_model.h"
#include "FrontEnd/mainwidget.h"
#include "FrontEnd/registerwidget.h"
#include "DatabaseTools/SQLiteDatabase.h"
#include "../HardwareSkeletonCode/ToolScanner.h"

int main(int argc, char *argv[])
{
    Missing_Model model;
    QApplication app(argc, argv);

    QWidget window;
    window.resize(600, 300);
    window.setWindowTitle
          (QApplication::translate("childwidget", "Child widget"));
    window.show();

    vector<int> missing;
    QStringList output;
    
    cout << "xxxx";

    ToolScanner* tl = new ToolScanner();
    SQLiteDatabase* db_tools = new SQLiteDatabase("ToolBox.db", tl);
    
    cout << "abcd";
    
    missing = db_tools->getMissingIDs();
    cout << missing.size();
    for (int i = 0; i < missing.size(); i++){
        cout << missing[i];
        output.append(missing[i] + "");
    }

    MissingWidget *widget = new MissingWidget(&window);
    widget->show();
    
    //all that is needed for reloading data
    widget->SetData(output);
    widget->loadView();
    
    RegisterWidget *regwidget = new RegisterWidget(&window);
    regwidget->move(400, 150);
    regwidget->show();

    return app.exec();



}
