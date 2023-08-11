#ifndef RESIZEWIDGET_H
#define RESIZEWIDGET_H

#include <QWidget>
#include <QPainter>


#include "mainwindow.h"

class ResizeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ResizeWidget(QWidget *parent = nullptr);
    void setMasterWindow(MainWindow* masterWindow);

private:
    void paintEvent(QPaintEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    MainWindow* masterWindow = nullptr;

    bool is_dragged = false;
    int absolute_pos_x;
    int absolute_pos_y;
    int prev_pos_x;
    int prev_pos_y;
    int prev_size_x;
    int prev_size_y;

};

#endif // RESIZEWIDGET_H
