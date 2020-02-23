// model.h
// https://helloacm.com/model-view-controller-explained-in-c/
#pragma once
#include <string>
#include <QStringList>
using namespace std;
//#include "common.h"
// Model is responsible for data get and set
class Missing_Model {
    public:
        Missing_Model(  QStringList s) {//const string &data) {
            this->SetData(s);
        }
        Missing_Model() { } // default constructor
        QStringList Data(){
            return this->data;
        }

        void SetData(  QStringList s) {//const string &data) {
            this->data = s;
            // if (this->event != nullptr) { // data change callback event
            //     this->event(s);
            // }
        }
        //  register the event when data changes.
        // void RegisterDataChangeHandler(DataChangeHandler handler) {
        //     this->event = handler;
        // }
    private:
        QStringList data;   //string data = "";
        //DataChangeHandler event = nullptr;
};
