#pragma once
#include <QWidget>
#include <QPaintEvent>
#include <memory>

class MyWidget : public QWidget
{
public:
    MyWidget(QWidget* parent = nullptr);
    void setFilePath(QString new_file_path);
    void setChannel(int channel01);
    void setBrother(MyWidget* brother);
    void setStartPoint(unsigned long long start_point);
    long long start_point = 0;



protected:
    void paintEvent(QPaintEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void wheelEvent(QWheelEvent *event) override;

    QString file_path;
    MyWidget* brother = nullptr;
    int channel01 = 0;
    int drag_x_start;
    bool is_dragged = false;
};
