#include "mywidget.h"

#include "filerd.h"

#include <cmath>

#include <QPainter>
#include <QPixmap>
#include <QDebug>


MyWidget::MyWidget(QWidget* parent) : QWidget(parent) {
    this->setMouseTracking(true);
}

void MyWidget::paintEvent(QPaintEvent *event){
    QPainter p(this);
//
    if(this->file_path != ""){
        auto signal = MYsignal(this->file_path.toStdString(), "int16");

        this->start_point = max((long long)0, (long long)this->start_point);
        this->start_point = min((long long)this->start_point, (long long)signal.get_length());

        if ((this->brother != nullptr) && (this->brother->start_point != this->start_point)){
            this->brother->setStartPoint(this->start_point);
            this->brother->update();
            qDebug() << "sent from" << this->channel01 << " " << this->start_point;
        }

        auto buff = signal.get_batch_1c(this->start_point, this->width(), this->channel01);
        //auto smth = max(signal.get_batch_1c(500, 4000, this->channel01));
        int height = this->height();
        int zero_line = height/2;
        double coef = (double) height / (double)pow(2,16);

        QPen zero_line_pen;
        zero_line_pen.setColor(Qt::red);
        zero_line_pen.setStyle(Qt::DashDotDotLine);
        zero_line_pen.setCosmetic(true);
        p.setPen(zero_line_pen);
        p.drawLine(0, zero_line, this->width(), zero_line);

        QPen grid_pen;
        grid_pen.setColor(QColor(127,127,127));
        grid_pen.setStyle(Qt::SolidLine);
        grid_pen.setWidthF(0.1);

        grid_pen.setCosmetic(true);
        p.setPen(grid_pen);

        int vert_grid_step = pow(2,13);
        for (int i = vert_grid_step; i < pow(2,15); i+= vert_grid_step){
            p.drawLine(0,  zero_line - (i * coef), this->width(), zero_line - (i * coef));
            p.drawLine(0,  zero_line + (i * coef), this->width(), zero_line + (i * coef));

        }

        zero_line_pen.setColor(Qt::green);
        zero_line_pen.setStyle(Qt::SolidLine);
        p.setPen(zero_line_pen);


        for(unsigned long long ind = 0; ind < buff.size()-1; ind++){
            p.drawLine(ind,
                       zero_line - (buff[ind] * coef),
                       ind,
                       zero_line - (buff[ind+1] * coef));
        }
    }
    //qDebug() << "update!";
}


void MyWidget::mouseMoveEvent(QMouseEvent *event){
    if (this->is_dragged){
        qDebug() << this->start_point;
        this-> start_point -= (event->pos().rx() - this->drag_x_start);
        this->drag_x_start = event->pos().rx();
        this->update();
    }
    qDebug() << "event";
}

void MyWidget::mousePressEvent(QMouseEvent *event){
    this->is_dragged=true;
}

void MyWidget::mouseReleaseEvent(QMouseEvent *event){
    this->is_dragged=false;
//    qDebug() << "rele" << event->pos();
}

void MyWidget::setBrother(MyWidget* brother){
    this->brother = brother;
}
void MyWidget::setStartPoint(unsigned long long start_point){
    this->start_point = start_point;
}


void MyWidget::setFilePath(QString new_file_path){
    this->file_path = new_file_path;
}

void MyWidget::setChannel(int channel01){
    if ((channel01 == 0) || (channel01 == 1))
        this->channel01 = channel01;
    else
        throw invalid_argument("\"channel01\" must be 0 or 1 (got " + to_string(channel01) + ")");
}
