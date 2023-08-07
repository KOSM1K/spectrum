#include "mainwindow.h"
#include "graphic.h"


#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow *win1 = new QMainWindow();
    win1->resize(500,500);
    win1->show();
    QGraphicsScene *scene = new QGraphicsScene(win1);
    scene->addWidget(graphic(win1->centralWidget()));
//    QGraphicsView view(scene, win1);
//    view.show();
//    view.resize(500,500);

//    QPixmap *pix = new QPixmap(500,500);
//    QGraphicsPixmapItem* item(scene->addPixmap(*pix)); // Save the returned item
//    QPainter *paint = new QPainter(pix);
//    paint->setPen(*(new QColor(255,34,255,255)));
//    paint->drawRect(15,15,100,100);
//    item->setPixmap(*pix); // Added this line

    return a.exec();
}
