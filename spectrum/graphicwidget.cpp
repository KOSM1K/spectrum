#include "graphicwidget.h"

#include "filerd.h"

#include <cmath>

#include <QPainter>
#include <QPixmap>
#include <QDebug>



GraphicWidget::GraphicWidget(QWidget* parent) : QWidget(parent) {
    this->setMouseTracking(true);
}


// painter
// separate to different functions!!!
void GraphicWidget::paintEvent(QPaintEvent *event){
    this->painter.begin(this);
    this->painter.fillRect(event->rect(), Qt::black);
    if(this->file_path != ""){
        auto signal = MYsignal(this->file_path.toStdString(), "int16");

        this->start_point = max((long long)0, (long long)this->start_point);
        this->start_point = min((long long)this->start_point, (long long)signal.get_length());

        if ((this->brother != nullptr) && (this->brother->start_point != this->start_point)){
            this->brother->setStartPoint(this->start_point);
            this->brother->update();
        }

        auto buff = signal.get_batch_1c(this->start_point, this->width() * pow(2, this->aspect_ratio), this->channel01);
        int height = this->height();
        int zero_line = height/2;
        double coef = (double) height / (double)pow(2,16);

        QPen zero_line_pen;
        zero_line_pen.setColor(Qt::red);
        zero_line_pen.setStyle(Qt::DashDotDotLine);
        zero_line_pen.setCosmetic(true);
        this->painter.setPen(zero_line_pen);
        this->painter.drawLine(0, zero_line, this->width(), zero_line);

        QPen grid_pen;
        grid_pen.setColor(QColor(127,127,127));
        grid_pen.setStyle(Qt::SolidLine);
        grid_pen.setWidthF(0.1);

        grid_pen.setCosmetic(true);
        this->painter.setPen(grid_pen);

        int vert_grid_step = pow(2,13);
        for (int i = vert_grid_step; i < pow(2,15); i+= vert_grid_step){
            this->painter.drawLine(0,  zero_line - (i * coef), this->width(), zero_line - (i * coef));
            this->painter.drawLine(0,  zero_line + (i * coef), this->width(), zero_line + (i * coef));

        }

        zero_line_pen.setColor(Qt::green);
        zero_line_pen.setStyle(Qt::SolidLine);
        this->painter.setPen(zero_line_pen);


        for(unsigned long long ind = 0; ind < this->width(); ind++){
            long long max_ = -100000000;
            long long min_ = 100000000;
            for (unsigned long long buff_index = ind * pow(2, this->aspect_ratio); buff_index < (ind + 1) * pow(2, this->aspect_ratio); buff_index++){
                max_ = max((long long)buff[buff_index], max_);
                min_ = min((long long)buff[buff_index], min_);
            }
            this->painter.drawLine(ind, zero_line - (min_ * coef), ind, zero_line - (max_ * coef));
        }
    }
    this->painter.end();
}



// control events

// drag events
void GraphicWidget::mouseMoveEvent(QMouseEvent *event){
    if (this->is_dragged){
        //qDebug() << this->start_point;
        this-> start_point -= (event->pos().rx() - this->drag_x_start) * pow(2,this->aspect_ratio);
        this->drag_x_start = event->pos().rx();
        this->update();
    }
}

void GraphicWidget::mousePressEvent(QMouseEvent *event){
    this->drag_x_start = event->pos().rx();
    this->is_dragged=true;
}

void GraphicWidget::mouseReleaseEvent(QMouseEvent *event){
    this->is_dragged=false;
}

// zoom events
void GraphicWidget::wheelEvent(QWheelEvent *event){
    qDebug() << event->angleDelta();
    this->aspect_ratio -= (event->angleDelta().y() /120);
    qDebug() << this->aspect_ratio;
    this->aspect_ratio = max(aspect_ratio, 0);
    this->update();
}

// dual channel sync
void GraphicWidget::setBrother(GraphicWidget* brother){
    this->brother = brother;
}
void GraphicWidget::setStartPoint(unsigned long long start_point){
    this->start_point = start_point;
}



// init functions
void GraphicWidget::setFilePath(QString new_file_path){
    this->file_path = new_file_path;
}

void GraphicWidget::setChannel(int channel01){
    if ((channel01 == 0) || (channel01 == 1))
        this->channel01 = channel01;
    else
        throw invalid_argument("\"channel01\" must be 0 or 1 (got " + to_string(channel01) + ")");
}
