#include <QtWidgets>
#include "registerwidget.h"
#include <iostream>
#include <QDebug>

// Constructor for main window
RegisterWidget::RegisterWidget(QWidget *parent) :
    QWidget(parent)
{
   //foo = new QString();
   button_ = new QPushButton(tr("Register Tools"));
   //textBrowser_ = new QTextBrowser();
   // QString str = "A,B,C,D,E,F,G,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v";
   // model.SetData(str.split(","));
   // for ( const auto& i : model.Data()  )
   // {
   //   textBrowser_->append(i);
   // }

   QGridLayout *mainLayout = new QGridLayout;
   mainLayout->addWidget(button_,0,0);
   //mainLayout->addWidget(textBrowser_,1,0);
   setLayout(mainLayout);
   //setWindowTitle(tr("Missing Tools"));

   connect(button_, SIGNAL(released()), this, SLOT(onButtonReleased()));
   connect(&process_, SIGNAL(readyReadStandardOutput()), this, SLOT(onCaptureProcessOutput()));
}

// Destructor
RegisterWidget::~RegisterWidget()
{
    delete button_;
   //delete textBrowser_;
}

// Handler for button click
void RegisterWidget::onButtonReleased()
{
    //foo = textBrowser_->toPlainText();
    // clear the text in the textBrowser and start the process
    //textBrowser_->clear();
    //box.setText("Enter Name of New Tool");
    //box.text();
    box.exec();
/////////////////    if (isOkPressed){
      foo = box.textValue();
      qDebug() << foo;
   ///////////////// }


    // Set up our process to write to stdout and run our command
    process_.setCurrentWriteChannel(QProcess::StandardOutput); // Set the write channel
    process_.start("ls -alh $HOME/desktop"); // Start a terminal command
}


// This is called whenever the QProcess::readyReadStandardOutput() signal is received
void RegisterWidget::onCaptureProcessOutput()
{
   qDebug() << "kldsajflkadflk";
   int i;
   //*QMessageBox _box = new QMessageBox();
   // Determine whether the object that sent the signal was a pointer to a process
   QProcess* process = qobject_cast<QProcess*>(sender());
   // If so, append the output to the textbrowser
   if (process)
      i = 0;
       //textBrowser_->append(process->readAllStandardOutput());
}
