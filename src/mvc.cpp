// mvc.cpp
#include <iostream>
#include <unistd.h>
#include <QString>
#include <QStringList>
#include <unistd.h>
#include <QTest>
#include <QElapsedTimer>
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

    int dbsize = 10000;
    ToolScanner* tl = new ToolScanner();
    SQLiteDatabase* db_tools = new SQLiteDatabase("test_databases/ToolBox" + to_string(dbsize) + ".db", tl);

    QWidget window;
    window.resize(600, 300);
    window.setWindowTitle
          (QApplication::translate("childwidget", "Child widget"));
    window.show();

    vector<int> missing;
    QStringList output;

    RegisterWidget *regwidget = new RegisterWidget(&window);
    regwidget->move(400, 150);
    regwidget->show();

    missing = db_tools->getMissingIDs();

    for (int i = 0; i < missing.size(); i++){
        output.append(missing[i] + "");
    }

    MissingWidget *widget = new MissingWidget(&window);
    widget->show();
    widget->SetData(output);
    widget->loadView();

    return app.exec();



}
