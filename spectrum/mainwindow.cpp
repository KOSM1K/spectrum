#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /* Инициализируем виджет с графикой
    myPicture1   = new MyGraphicView(0, ui ->label, 0);
    //myPicture2   = new MyGraphicView(0, ui ->label, 1);
    /* и добавляем его на слой
    ui->graphicLayout->addWidget(myPicture1);
    //ui->graphicLayout->addWidget(myPicture2);*/

}

MainWindow::~MainWindow()
{
    delete ui;
}

