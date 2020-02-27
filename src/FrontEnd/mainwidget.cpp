#include <QtWidgets>
#include "mainwidget.h"
#include <iostream>
#include <QDebug>

// Constructor for main window
MissingWidget::MissingWidget(QWidget *parent) :
    QWidget(parent)
{
   //foo = new QString();
    button_ = new QPushButton(tr("Limit Switch"));
   textBrowser_ = new QTextBrowser();
   textBrowser_->resize(800,600);
   for ( const auto& i : model.Data()  )
   {
     textBrowser_->append(i);
   }

   QGridLayout *mainLayout = new QGridLayout;
   mainLayout->addWidget(button_,0,0);
   mainLayout->addWidget(textBrowser_,1,0);
   setLayout(mainLayout);
   setWindowTitle(tr("Missing Tools"));
   
   tl = new ToolScanner;
   db_tools = new SQLiteDatabase("../dbFiles/ToolBox100.db", tl);
   db_tools->addTool(to_string(22319), "Tag F5");
    db_tools->addTool(to_string(52885), "Tag T2");
    db_tools->addTool(to_string(140), "Tag T1");
    db_tools->addTool(to_string(53644), "Tag T3");
    db_tools->addTool(to_string(309), "Tag T4");
    //db_tools->addTool(to_string(1), "Tag T10");

   connect(button_, SIGNAL(released()), this, SLOT(onButtonReleased()));
   connect(&process_, SIGNAL(readyReadStandardOutput()), this, SLOT(onCaptureProcessOutput()));
}

// Destructor
MissingWidget::~MissingWidget()
{
    delete button_;
   delete textBrowser_;
   delete tl;
   delete db_tools;
}

// void MissingWidget::SetData(Missing_Model list){
//   model = list;
// }
void MissingWidget::SetData(QStringList list){
  model.SetData(list);
}

void MissingWidget::loadView(){
  textBrowser_->clear();
  for ( const auto& i : model.Data()  )
  {
    textBrowser_->append(i);
  }
}

// Handler for button click
void MissingWidget::onButtonReleased()
{
    //foo = textBrowser_->toPlainText();
    // clear the text in the textBrowser and start the process
    textBrowser_->clear();
    //box.setText("Enter Name of New Tool");
    //box.text();
    // box.exec();
    // foo = box.textValue();
    // qDebug() << foo;
    
    //Gets the missing tools
    vector<string> missing;
    QStringList output;
    
    missing = db_tools->getMissingToolIDs();
    //cout<<"Test " <<endl;
    
    //Converts into UI string object
    for (int i = 0; i < missing.size(); i++){
        QString next = QString::fromStdString(missing[i]);
        //cout << missing[i] << "\n";
        output.append(next);
    }

    //all that is needed for reloading data
    SetData(output);
    loadView();

    // Set up our process to write to stdout and run our command
    process_.setCurrentWriteChannel(QProcess::StandardOutput); // Set the write channel
    process_.start("ls -alh $HOME/desktop"); // Start a terminal command
}


// This is called whenever the QProcess::readyReadStandardOutput() signal is received
void MissingWidget::onCaptureProcessOutput()
{
   qDebug() << "kldsajflkadflk";
   //*QMessageBox _box = new QMessageBox();
   // Determine whether the object that sent the signal was a pointer to a process
   QProcess* process = qobject_cast<QProcess*>(sender());
   // If so, append the output to the textbrowser
   if (process)
       textBrowser_->append(process->readAllStandardOutput());
}
