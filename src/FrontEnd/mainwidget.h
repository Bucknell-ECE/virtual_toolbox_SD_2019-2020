#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "missing_model.h"
#include <QWidget>
#include <QProcess>
#include <QInputDialog>
#include "../DatabaseTools/SQLiteDatabase.h"
#include "../UWBDriverCode/ToolScanner.h"

class QPushButton;
class QTextBrowser;

// This is the declaration of our MainWidget class
// The definition/implementation is in mainwidget.cpp
class MissingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MissingWidget(QWidget *parent = 0, SQLiteDatabase *sqlitedb = 0, ToolScanner *toolscanner = 0); //Constructor
    ~MissingWidget(); // Destructor
    void SetData(QStringList list);
    void loadView();


private slots:
    void onButtonReleased(); // Handler for button presses
    void onCaptureProcessOutput(); // Handler for Process output

private:
   QPushButton* button_;
   QTextBrowser* textBrowser_;
   ToolScanner* tl;
   SQLiteDatabase* db_tools;//("../dbFiles/ToolBox100.db", tl);
   QProcess process_;   // This is the process the button will fire off
   // QString foo;
   // QInputDialog box;
   Missing_Model model;
};

#endif // MAINWIDGET_H
