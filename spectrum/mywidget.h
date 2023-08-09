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



protected:
    void paintEvent(QPaintEvent *event) override;

    QString file_path;
    int channel01 = 0;
};
