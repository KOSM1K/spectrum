#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <mygraphicview.h>
//#include <mywidget.h>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
//    MyGraphicView   *myPicture1;
//    MyGraphicView   *myPicture2;
   // MyWidget *mywidget;

};
#endif // MAINWINDOW_H
