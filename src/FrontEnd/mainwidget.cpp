#include <QtWidgets>
#include "mainwidget.h"
#include <iostream>
#include <QDebug>

// Constructor for main window
MissingWidget::MissingWidget(QWidget *parent) :
    QWidget(parent)
{
   //foo = new QString();
    button_ = new QPushButton(tr("Dismiss"));
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

   connect(button_, SIGNAL(released()), this, SLOT(onButtonReleased()));
   connect(&process_, SIGNAL(readyReadStandardOutput()), this, SLOT(onCaptureProcessOutput()));
}

// Destructor
MissingWidget::~MissingWidget()
{
    delete button_;
   delete textBrowser_;
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
