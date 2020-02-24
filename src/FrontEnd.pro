######################################################################
# Automatically generated by qmake (3.1) Tue Feb 11 15:05:05 2020
######################################################################

QT += widgets
QT += testlib
QT += sql
TEMPLATE = app
TARGET = VirtualToolbox
INCLUDEPATH += $$PWD
LIBS += -ldl
LIBS += -pthread
#QMAKE_CFLAGS += -ldl -pthread
#LIBS += QtSql.lib

# You can make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# Please consult the documentation of the deprecated API in order to know
# how to port your code away from it.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += FrontEnd/missing_model.h \
           FrontEnd/registerwidget.h \
	   FrontEnd/mainwidget.h \
	   DatabaseTools/SQLiteDatabase.h \
	   ../HardwareSkeletonCode/ToolScanner.h \
	   ../sqlite3/sqlite3.h \
	   DatabaseTools/CallbackFunctions.cpp
	   #dlfcn.h	   
	   
SOURCES += mvc.cpp \
           FrontEnd/registerwidget.cpp \
	   FrontEnd/mainwidget.cpp \
	   DatabaseTools/SQLiteDatabase.cpp \
	   ../HardwareSkeletonCode/ToolScanner.cpp \
	   ../sqlite3/sqlite3.c \
	   DatabaseTools/CallbackFunctions.cpp
