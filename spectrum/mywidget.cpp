#include "mywidget.h"

#include "filerd.h"

#include <cmath>

#include <QPainter>
#include <QPixmap>
#include <QDebug>


MyWidget::MyWidget(QWidget* parent) : QWidget(parent) {

}

void MyWidget::paintEvent(QPaintEvent *event){
    QPainter p(this);
    p.fillRect(event->rect(), Qt::black);
    if(this->file_path != ""){
        auto signal = MYsignal(this->file_path.toStdString(), "int16");
        auto buff = signal.get_batch_1c(500, 4000, this->channel01);

        int height = this->height();
        int zero_line = height/2;

        p.setPen(Qt::red);
        p.drawLine(0, zero_line, this->width(), zero_line);
        p.setPen(Qt::green);

        double coef = (double) height / (double)pow(2,16);

        for(int ind = 0; ind < buff.size()-1; ind++){
            p.drawLine(ind,
                       zero_line - (buff[ind] * coef),
                       ind,
                       zero_line - (buff[ind+1] * coef));
        }
    }
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
