#ifndef REGISTERWIDGET_H
#define REGISTERWIDGET_H

#include <QWidget>
#include <QProcess>
#include <QInputDialog>

class QPushButton;
class QTextBrowser;

// This is the declaration of our MainWidget class
// The definition/implementation is in mainwidget.cpp
class RegisterWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterWidget(QWidget *parent = 0); //Constructor
    ~RegisterWidget(); // Destructor
    

private slots:
    void onButtonReleased(); // Handler for button presses
    void onCaptureProcessOutput(); // Handler for Process output

private:
   QPushButton* button_;
   //QTextBrowser* textBrowser_;
   QProcess process_;   // This is the process the button will fire off
   QString foo;
   QInputDialog box;
   //Missing_Model model;
};

#endif // MAINWIDGET_H
