/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <dragwidget.h>
#include <graphicwidget.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QWidget *resize_widget;
    QLabel *label;
    DragWidget *drag_widget;
    QWidget *minimise_widget;
    QWidget *maximise_widget;
    QWidget *close_widget;
    QVBoxLayout *verticalLayout_2;
    GraphicWidget *widget_1;
    QSpacerItem *verticalSpacer;
    GraphicWidget *widget_2;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(855, 800);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(800, 800));
        MainWindow->setCursor(QCursor(Qt::ArrowCursor));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy1);
        centralwidget->setFocusPolicy(Qt::StrongFocus);
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        resize_widget = new QWidget(centralwidget);
        resize_widget->setObjectName("resize_widget");
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(resize_widget->sizePolicy().hasHeightForWidth());
        resize_widget->setSizePolicy(sizePolicy2);
        resize_widget->setMinimumSize(QSize(20, 20));
        resize_widget->setCursor(QCursor(Qt::SizeFDiagCursor));

        horizontalLayout->addWidget(resize_widget);

        label = new QLabel(centralwidget);
        label->setObjectName("label");
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy3);
        label->setMinimumSize(QSize(0, 20));

        horizontalLayout->addWidget(label, 0, Qt::AlignLeft);

        drag_widget = new DragWidget(centralwidget);
        drag_widget->setObjectName("drag_widget");
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(drag_widget->sizePolicy().hasHeightForWidth());
        drag_widget->setSizePolicy(sizePolicy4);
        drag_widget->setMinimumSize(QSize(0, 20));

        horizontalLayout->addWidget(drag_widget);

        minimise_widget = new QWidget(centralwidget);
        minimise_widget->setObjectName("minimise_widget");
        sizePolicy2.setHeightForWidth(minimise_widget->sizePolicy().hasHeightForWidth());
        minimise_widget->setSizePolicy(sizePolicy2);
        minimise_widget->setMinimumSize(QSize(20, 20));

        horizontalLayout->addWidget(minimise_widget);

        maximise_widget = new QWidget(centralwidget);
        maximise_widget->setObjectName("maximise_widget");
        sizePolicy2.setHeightForWidth(maximise_widget->sizePolicy().hasHeightForWidth());
        maximise_widget->setSizePolicy(sizePolicy2);
        maximise_widget->setMinimumSize(QSize(20, 20));

        horizontalLayout->addWidget(maximise_widget);

        close_widget = new QWidget(centralwidget);
        close_widget->setObjectName("close_widget");
        sizePolicy2.setHeightForWidth(close_widget->sizePolicy().hasHeightForWidth());
        close_widget->setSizePolicy(sizePolicy2);
        close_widget->setMinimumSize(QSize(20, 20));

        horizontalLayout->addWidget(close_widget);


        verticalLayout->addLayout(horizontalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(6, 6, 6, 6);
        widget_1 = new GraphicWidget(centralwidget);
        widget_1->setObjectName("widget_1");

        verticalLayout_2->addWidget(widget_1);

        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer);

        widget_2 = new GraphicWidget(centralwidget);
        widget_2->setObjectName("widget_2");

        verticalLayout_2->addWidget(widget_2);


        verticalLayout->addLayout(verticalLayout_2);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        statusbar->setEnabled(true);
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Spectrum", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
