#include "mainwindow.h"
#include <QGuiApplication>
#include <QApplication>
#include <QStyle>

#include <iostream>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.setWindowTitle("Spectrum");
    w.setWindowFlags(Qt::FramelessWindowHint) ; // no title

    w.setStyleSheet("color: #FFFFFF;"
                    "background-color: #222222;"
                    "border-width: 1px;"
                    "border-style: solid;"
                    "border-color: #555555;"
                    "bottom: 0px");


//    w.setWindowOpacity(0.95);

    //make it draggable!!!


    //hint:

    //w.resize(2500,1000);
    //w.move(0,0); // moves window TO position (left upper anchor of main skreen is 0,0)

    //QCoreApplication::quit(); //native quit call from code

    //make a top widget with no spacing on siges and top
    //w.setWindowState(Qt::WindowMinimized); //свернуть
    //w.setWindowState(Qt::WindowMaximized); //развернуть (на весь экран (ну почти))
    //w.setWindowState(Qt::WindowFullScreen); //развернуть на весь экран
    //w.setWindowState(Qt::WindowNoState); //нормальное положение
    w.show();
    return a.exec();
}


//QFileSystemModel model;
//model.setFilter( QDir::Dirs | QDir::NoDotAndDotDot );
//model.setRootPath("");
//QTreeView tree;
//tree.setModel(&model);

//// Demonstrating look and feel features
//tree.setAnimated(false);
//tree.setIndentation(20);
//tree.setSortingEnabled(true);

//tree.setWindowTitle(QObject::tr("Dir View"));
//tree.resize(640, 480);
//tree.show();
