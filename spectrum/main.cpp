#include "mainwindow.h"

#include <QApplication>
#include <QFileSystemModel>
#include <QFileSelector>

#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

#include <iostream>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString fileName = QFileDialog::getOpenFileName(new QWidget, QFileDialog::tr("Open File"),
                                 "/home",
                                 QFileDialog::tr("*.pcm")
                                 );

    qDebug() << "The file you chose is " << fileName;

    MainWindow w;
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
