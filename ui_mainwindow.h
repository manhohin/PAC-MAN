/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include "graphics.h"
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    GameWidget *widget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *player_b_score;
    QLabel *player_a_score;
    QWidget *side_menu;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1528, 948);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        widget = new GameWidget(MainWindow);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setStyleSheet(QString::fromUtf8("QWidget#centralwidget{\n"
                                                "background-image: url(:/resources/images/stripes.png);\n"
                                                "};"));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        player_b_score = new QLabel(widget);
        player_b_score->setObjectName(QString::fromUtf8("player_b_score"));
        player_b_score->setAlignment(Qt::AlignLeading | Qt::AlignLeft | Qt::AlignTop);

        horizontalLayout->addWidget(player_b_score);

        player_a_score = new QLabel(widget);
        player_a_score->setObjectName(QString::fromUtf8("player_a_score"));
        player_a_score->setAlignment(Qt::AlignRight | Qt::AlignTop | Qt::AlignTrailing);

        horizontalLayout->addWidget(player_a_score);

        verticalLayout->addLayout(horizontalLayout);

        side_menu = new QWidget(widget);
        side_menu->setObjectName(QString::fromUtf8("side_menu"));
        side_menu->setMaximumSize(QSize(400, 16777215));
        QFont font;
        font.setFamily({QString::fromUtf8("Comic Sans MS")});
        font.setPointSize(14);
        side_menu->setFont(font);
        side_menu->setLayoutDirection(Qt::RightToLeft);

        verticalLayout->addWidget(side_menu);

        MainWindow->setCentralWidget(widget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Simple Map", nullptr));
        player_b_score->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        player_a_score->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
    } // retranslateUi
};

namespace Ui
{
class MainWindow : public Ui_MainWindow
{
};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
