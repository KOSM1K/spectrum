#include "graphic.h"

graphic::graphic(QWidget *parent) : QWidget(parent)
{

}

void graphic::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.drawLine(0,0,100,100);
}

