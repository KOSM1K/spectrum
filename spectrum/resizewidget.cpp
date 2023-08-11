#include "resizewidget.h"
#include "qevent.h"

ResizeWidget::ResizeWidget(QWidget *parent)
    : QWidget{parent}
{

}


void ResizeWidget::paintEvent(QPaintEvent *event){
    auto p = QPainter(this);
    auto pen = QPen();
    pen.setColor(Qt::white);
    pen.setCosmetic(true);
    p.setPen(pen);
    p.fillRect(1,1,2,2, Qt::white);
    p.fillRect(1,5,2,2, Qt::white);
    p.fillRect(1,9,2,2, Qt::white);
    p.fillRect(1,1,2,2, Qt::white);
    p.fillRect(5,1,2,2, Qt::white);
    p.fillRect(9,1,2,2, Qt::white);
    p.fillRect(5,5,2,2, Qt::white);
}


void ResizeWidget::mouseMoveEvent(QMouseEvent *event){
//    qDebug() << this->absolute_pos_x << " " << event->pos().x() << " " << this->absolute_pos_y << " " << event->pos().y() << " " << this->prev_pos_x << " " << this->prev_pos_y;
//    qDebug() << this->masterWindow->size();

    if (this->is_dragged){
        auto delta_x = (this->masterWindow->pos().x() + event->pos().x() - this->absolute_pos_x);
        auto delta_y = (this->masterWindow->pos().y() + event->pos().y() - this->absolute_pos_y);

        this->masterWindow->resize(this->prev_size_x - delta_x, this->prev_size_y - delta_y);

        delta_x = (this->masterWindow->size().width() - this->prev_size_x);
        delta_y = (this->masterWindow->size().height() - this->prev_size_y);

        auto cur_pos_x = this->prev_pos_x - delta_x;
        auto cur_pos_y = this->prev_pos_y - delta_y;

        this->masterWindow->move(cur_pos_x, cur_pos_y);
    }
}
void ResizeWidget::mousePressEvent(QMouseEvent *event){
    if (!is_dragged){
        this->is_dragged = true;
        this->absolute_pos_x = this->masterWindow->pos().x() + event->pos().x();
        this->absolute_pos_y = this->masterWindow->pos().y() + event->pos().y();
        this->prev_pos_x = this->masterWindow->pos().x();
        this->prev_pos_y = this->masterWindow->pos().y();
        this->prev_size_x = this->masterWindow->size().width();
        this->prev_size_y = this->masterWindow->size().height();

    }

}
void ResizeWidget::mouseReleaseEvent(QMouseEvent *event){
    this->is_dragged = false;
}

void ResizeWidget::setMasterWindow(MainWindow* masterWindow){
    this->masterWindow = masterWindow;
}
