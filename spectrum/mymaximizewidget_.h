#ifndef MYMAXIMIZEWIDGET__H
#define MYMAXIMIZEWIDGET__H

#include <QWidget>
#include <QPainter>
#include "mainwindow.h"



class MyMaximizeWidget_ : public QWidget
{
    Q_OBJECT
public:
    explicit MyMaximizeWidget_(QWidget *parent = nullptr);
    void setMasterWindow(MainWindow* masterWindow);

private:
    void paintEvent(QPaintEvent *event) override;

    void enterEvent(QEnterEvent* event) override;
    void leaveEvent(QEvent* event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    MainWindow* masterWindow = nullptr;

    bool hoversOver = false;
    bool maximized = false;

};

#endif // MYMAXIMIZEWIDGET__H
