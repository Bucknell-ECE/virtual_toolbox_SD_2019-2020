#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "missing_model.h"
#include <QWidget>
#include <QProcess>
#include <QInputDialog>

class QPushButton;
class QTextBrowser;

// This is the declaration of our MainWidget class
// The definition/implementation is in mainwidget.cpp
class MissingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MissingWidget(QWidget *parent = 0); //Constructor
    ~MissingWidget(); // Destructor
    void SetData(QStringList list);
    void loadView();

private slots:
    void onButtonReleased(); // Handler for button presses
    void onCaptureProcessOutput(); // Handler for Process output

private:
   QPushButton* button_;
   QTextBrowser* textBrowser_;
   QProcess process_;   // This is the process the button will fire off
   // QString foo;
   // QInputDialog box;
   Missing_Model model;
};

#endif // MAINWIDGET_H
