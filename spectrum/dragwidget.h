#ifndef DRAGWIDGET_H
#define DRAGWIDGET_H

#include<QWidget>

#include "mainwindow.h"

class DragWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DragWidget(QWidget *parent = nullptr);
    void setMasterWindow(MainWindow* masterWindow);

private:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    MainWindow* masterWindow = nullptr;

    bool is_dragged = false;
    int absolute_pos_x;
    int absolute_pos_y;
    int prev_pos_x;
    int prev_pos_y;

};

#endif // DRAGWIDGET_H
