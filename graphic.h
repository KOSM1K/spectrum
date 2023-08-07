#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <QWidget>
#include <QPainter>


class graphic : public QWidget
{
    Q_OBJECT
public:
    explicit graphic(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

};

#endif // GRAPHIC_H
