#include "closewidget.h"
#include "qevent.h"

#include <QCoreApplication>

CloseWidget::CloseWidget(QWidget *parent)
    : QWidget{parent}
{

}

void CloseWidget::paintEvent(QPaintEvent *event){
    auto p = QPainter(this);
    auto pen = QPen();
    pen.setWidth(2);
    if (hoversOver){
        p.fillRect(event->rect(), Qt::red);
        pen.setColor(Qt::black);
        p.setPen(pen);
        p.drawLine(5,5,15,15);
        p.drawLine(5,15,15,5);
    }
    else{
        p.fillRect(event->rect(), QColor(0x222222));
        pen.setColor(Qt::red);
        p.setPen(pen);
        p.drawLine(5,5,15,15);
        p.drawLine(5,15,15,5);
    }
}

void CloseWidget::setMasterWindow(MainWindow* masterWindow){
    this->masterWindow = masterWindow;
}

void CloseWidget::enterEvent(QEnterEvent* event){
    this->hoversOver = true;
    this->update();
}
void CloseWidget::leaveEvent(QEvent* event){
    this->hoversOver = false;
    this->update();
}
void CloseWidget::mouseReleaseEvent(QMouseEvent *event){
    if (this->hoversOver){
        QCoreApplication::quit();
    }
}
