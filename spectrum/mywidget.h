#pragma once
#include <QWidget>
#include <QPaintEvent>
#include "acqsignal.h"
#include <memory>

class MyWidget : public QWidget
{
public:
    MyWidget(QWidget* parent = nullptr);


protected:
    void paintEvent(QPaintEvent *event) override;
    std::unique_ptr<acqSignal> pSignal;
};
