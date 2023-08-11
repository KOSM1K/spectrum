#ifndef CLOSEWIDGET_H
#define CLOSEWIDGET_H

#include <QWidget>
#include <QPainter>
#include "mainwindow.h"


class CloseWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CloseWidget(QWidget *parent = nullptr);
    void setMasterWindow(MainWindow* masterWindow);

private:
    void paintEvent(QPaintEvent *event) override;

    void enterEvent(QEnterEvent* event) override;
    void leaveEvent(QEvent* event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    MainWindow* masterWindow = nullptr;

    bool hoversOver = false;

};

#endif // CLOSEWIDGET_H
