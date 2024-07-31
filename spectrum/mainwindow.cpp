#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileSystemModel>
#include <QFileSelector>

#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString fileName = QFileDialog::getOpenFileName(new QWidget, QFileDialog::tr("Spectrum - open file"),
                                                    "../spectrum_git/Spectrum_test/",
                                                    QFileDialog::tr("*.pcm")
                                                    );

    qDebug() << "The file you chose is " << fileName;
    ui->widget_1->setFilePath(fileName);
    ui->widget_1->setChannel(0);

    ui->widget_2->setFilePath(fileName);
    ui->widget_2->setChannel(1);


    ui->widget_2->setBrother(ui->widget_1);
    ui->widget_1->setBrother(ui->widget_2);

    ui->drag_widget->setMasterWindow(this);
    // ui->resize_widget->setMasterWindow(this);
    ui->close_widget->setMasterWindow(this);
    ui->my_maximize_widget->setMasterWindow(this);
    ui->my_minimize_widget->setMasterWindow(this);






    this->createStatusBar();

}

void MainWindow::createStatusBar()
{
//    auto c = new QLabel("jkgdfhjgh");
    this->statusBar()->showMessage("Ready (mainwindow cpp)");
}

MainWindow::~MainWindow()
{
    delete ui;
}
