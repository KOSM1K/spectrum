#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileSystemModel>
#include <QFileSelector>

#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString fileName = QFileDialog::getOpenFileName(new QWidget, QFileDialog::tr("Open File"),
                                                    "../spectrum_github/Spectrum_test",
                                                    QFileDialog::tr("*.pcm")
                                                    );

    qDebug() << "The file you chose is " << fileName;
    ui->widget_1->setFilePath(fileName);
    ui->widget_1->setChannel(0);

    ui->widget_2->setFilePath(fileName);
    ui->widget_2->setChannel(1);
    //    ui->widget_3->setFilePath(fileName);


}

MainWindow::~MainWindow()
{
    delete ui;
}
