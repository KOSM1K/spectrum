#include "myminimizewidget_.h"
#include "qevent.h"

#include <QCoreApplication>

MyMinimizeWidget_::MyMinimizeWidget_(QWidget *parent)
    : QWidget{parent}
{

}

void MyMinimizeWidget_::paintEvent(QPaintEvent *event){
    auto p = QPainter(this);
    auto pen = QPen();
    pen.setWidth(2);

    if (hoversOver){
        p.fillRect(event->rect(), Qt::white);
        pen.setColor(Qt::black);
        p.setPen(pen);
        p.drawLine(3,14,14,14);
    }
    else{
        p.fillRect(event->rect(), QColor(0x222222));
        pen.setColor(Qt::white);
        p.setPen(pen);

        p.drawLine(3,14,14,14);
    }
}

void MyMinimizeWidget_::setMasterWindow(MainWindow* masterWindow){
    this->masterWindow = masterWindow;
}

void MyMinimizeWidget_::enterEvent(QEnterEvent* event){
    this->hoversOver = true;
    this->update();
}
void MyMinimizeWidget_::leaveEvent(QEvent* event){
    this->hoversOver = false;
    this->update();
}
void MyMinimizeWidget_::mouseReleaseEvent(QMouseEvent *event){
    if (this->hoversOver){
        this->masterWindow->setWindowState(Qt::WindowMinimized);
    }
}
