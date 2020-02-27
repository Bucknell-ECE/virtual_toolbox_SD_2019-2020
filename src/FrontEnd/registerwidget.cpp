#include <QtWidgets>
#include "registerwidget.h"
#include <iostream>
#include <QDebug>

// Constructor for main window
RegisterWidget::RegisterWidget(QWidget *parent, SQLiteDatabase *db_tools, ToolScanner *tl) :
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
   
   db_tools = db_tools;
   tl = tl;

   connect(button_, SIGNAL(released()), this, SLOT(onButtonReleased()));
   connect(&process_, SIGNAL(readyReadStandardOutput()), this, SLOT(onCaptureProcessOutput()));
}

// Destructor
RegisterWidget::~RegisterWidget()
{
    delete button_;
    delete tl;
    delete db_tools;
}

// Handler for button click
void RegisterWidget::onButtonReleased()
{
    int success;
    box.exec();
    foo = box.textValue();
    qDebug() << foo;
    //QString to string
    ///string name = foo.toUtf8().constData();
    ///success = db_tools->registerNewTool(name, tl);
    qDebug() << success;


    // Set up our process to write to stdout and run our command
    process_.setCurrentWriteChannel(QProcess::StandardOutput); // Set the write channel
    process_.start("ls -alh $HOME/desktop"); // Start a terminal command
}


// This is called whenever the QProcess::readyReadStandardOutput() signal is received
void RegisterWidget::onCaptureProcessOutput()
{
   qDebug() << "kldsajflkadflk";
   int i;
   QProcess* process = qobject_cast<QProcess*>(sender());
   // If so, append the output to the textbrowser
   if (process)
      i = 0;
}
