/********************************************************************************
** Form generated from reading UI file 'winwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINWINDOW_H
#define UI_WINWINDOW_H

#include "winwidget.h"
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WinWindow
{
public:
    WinWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;

    void setupUi(QMainWindow *WinWindow)
    {
        if (WinWindow->objectName().isEmpty())
            WinWindow->setObjectName(QString::fromUtf8("WinWindow"));
        WinWindow->resize(801, 600);
        WinWindow->setSizeIncrement(QSize(1, 0));
        centralwidget = new WinWidget(WinWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(200, 200, 371, 381));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMaximumSize(QSize(250000, 250000));
        label->setPixmap(QPixmap(QString::fromUtf8(":/images/congrats.png")));
        label->setScaledContents(true);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        WinWindow->setCentralWidget(centralwidget);

        retranslateUi(WinWindow);

        QMetaObject::connectSlotsByName(WinWindow);
    } // setupUi

    void retranslateUi(QMainWindow *WinWindow)
    {
        WinWindow->setWindowTitle(QCoreApplication::translate("WinWindow", "MainWindow", nullptr));
        label->setText(QString());
    } // retranslateUi
};

namespace Ui
{
class WinWindow : public Ui_WinWindow
{
};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINWINDOW_H
