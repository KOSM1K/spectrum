#include "dragwidget.h"
#include "qevent.h"
#include <QDebug>

DragWidget::DragWidget(QWidget *parent)
    : QWidget{parent}
{

}

void DragWidget::mouseMoveEvent(QMouseEvent *event){
    qDebug() << this->absolute_pos_x << " " << event->pos().x() << " " << this->absolute_pos_y << " " << event->pos().y() << " " << this->prev_pos_x << " " << this->prev_pos_y;


    if (this->is_dragged){
        auto cur_pos_x = this->prev_pos_x + (this->masterWindow->pos().x() + event->pos().x() - this->absolute_pos_x);
        auto cur_pos_y = this->prev_pos_y + (this->masterWindow->pos().y() + event->pos().y() - this->absolute_pos_y);
        this->masterWindow->move(cur_pos_x, cur_pos_y);
    }
}
void DragWidget::mousePressEvent(QMouseEvent *event){
    if (!is_dragged){
        this->is_dragged = true;
        this->absolute_pos_x = this->masterWindow->pos().x() + event->pos().x();
        this->absolute_pos_y = this->masterWindow->pos().y() + event->pos().y();
        this->prev_pos_x = this->masterWindow->pos().x();
        this->prev_pos_y = this->masterWindow->pos().y();
    }

}
void DragWidget::mouseReleaseEvent(QMouseEvent *event){
    this->is_dragged = false;
}

void DragWidget::setMasterWindow(MainWindow* masterWindow){
    this->masterWindow = masterWindow;
}
