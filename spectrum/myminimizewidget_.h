#ifndef MYMINIMIZEWIDGET__H
#define MYMINIMIZEWIDGET__H

#include <QWidget>
#include <QPainter>
#include "mainwindow.h"



class MyMinimizeWidget_ : public QWidget
{
    Q_OBJECT
public:
    explicit MyMinimizeWidget_(QWidget *parent = nullptr);
    void setMasterWindow(MainWindow* masterWindow);

private:
    void paintEvent(QPaintEvent *event) override;

    void enterEvent(QEnterEvent* event) override;
    void leaveEvent(QEvent* event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    MainWindow* masterWindow = nullptr;

    bool hoversOver = false;

};

#endif // MYMINIMIZEWIDGET__H
