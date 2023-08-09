#include "mywidget.h"
#include <QPainter>

MyWidget::MyWidget(QWidget* parent) : QWidget(parent) {

}

void MyWidget::paintEvent(QPaintEvent *event){
    QPainter p(this);
    p.fillRect(event->rect(), Qt::black);
    p.setPen(Qt::green);
    p.drawLine(0,0,100,100);
}
