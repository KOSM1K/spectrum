#include "mymaximizewidget_.h"
#include "qevent.h"

#include <QCoreApplication>

MyMaximizeWidget_::MyMaximizeWidget_(QWidget *parent)
    : QWidget{parent}
{

}

void MyMaximizeWidget_::paintEvent(QPaintEvent *event){
    auto p = QPainter(this);
    auto pen = QPen();
    pen.setWidth(2);

    if (hoversOver){
        p.fillRect(event->rect(), Qt::blue);
        pen.setColor(Qt::black);
        p.setPen(pen);
        p.drawRect(3,3,14,14);
    }
    else{
        p.fillRect(event->rect(), QColor(0x222222));
        pen.setColor(Qt::blue);
        p.setPen(pen);

        p.drawRect(3,3,14,14);
    }
}

void MyMaximizeWidget_::setMasterWindow(MainWindow* masterWindow){
    this->masterWindow = masterWindow;
}

void MyMaximizeWidget_::enterEvent(QEnterEvent* event){
    this->hoversOver = true;
    this->update();
}
void MyMaximizeWidget_::leaveEvent(QEvent* event){
    this->hoversOver = false;
    this->update();
}
void MyMaximizeWidget_::mouseReleaseEvent(QMouseEvent *event){
    if (this->hoversOver){
        if (this->maximized){
            this->masterWindow->setWindowState(Qt::WindowNoState);
            maximized = false;
        }
        else{
            this->masterWindow->setWindowState(Qt::WindowMaximized);
            maximized = true;
        }

    }
}
