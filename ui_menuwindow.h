/********************************************************************************
** Form generated from reading UI file 'menuwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENUWINDOW_H
#define UI_MENUWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MenuWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QStackedWidget *pages;
    QWidget *page_main;
    QVBoxLayout *verticalLayout;
    QLabel *label_simplemap;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btn_load;
    QLabel *label_ack;
    QWidget *page_size_selection;
    QVBoxLayout *verticalLayout_3;

    void setupUi(QMainWindow *MenuWindow)
    {
        if (MenuWindow->objectName().isEmpty())
            MenuWindow->setObjectName(QString::fromUtf8("MenuWindow"));
        MenuWindow->resize(800, 600);
        MenuWindow->setAutoFillBackground(true);
        MenuWindow->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(MenuWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        pages = new QStackedWidget(centralwidget);
        pages->setObjectName(QString::fromUtf8("pages"));
        page_main = new QWidget();
        page_main->setObjectName(QString::fromUtf8("page_main"));
        verticalLayout = new QVBoxLayout(page_main);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_simplemap = new QLabel(page_main);
        label_simplemap->setObjectName(QString::fromUtf8("label_simplemap"));
        label_simplemap->setMaximumSize(QSize(1400, 700));
        label_simplemap->setPixmap(QPixmap(QString::fromUtf8(":/images/menu_pacman.png")));
        label_simplemap->setScaledContents(true);

        verticalLayout->addWidget(label_simplemap);

        widget = new QWidget(page_main);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);"));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        btn_load = new QPushButton(widget);
        btn_load->setObjectName(QString::fromUtf8("btn_load"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btn_load->sizePolicy().hasHeightForWidth());
        btn_load->setSizePolicy(sizePolicy);
        btn_load->setMaximumSize(QSize(200, 16777215));
        QFont font;
        font.setFamily({QString::fromUtf8("Comic Sans MS")});
        font.setPointSize(30);
        btn_load->setFont(font);
        btn_load->setAutoFillBackground(false);
        btn_load->setStyleSheet(QString::fromUtf8("\n"
                                                  "background-color: rgba(255, 255, 255, 0);\n"
                                                  "\n"
                                                  ""));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/start.png"), QSize(), QIcon::Normal, QIcon::On);
        btn_load->setIcon(icon);
        btn_load->setIconSize(QSize(200, 60));

        horizontalLayout_2->addWidget(btn_load);

        verticalLayout->addWidget(widget);

        label_ack = new QLabel(page_main);
        label_ack->setObjectName(QString::fromUtf8("label_ack"));
        label_ack->setEnabled(true);
        label_ack->setMaximumSize(QSize(2000, 1000));
        QFont font1;
        font1.setFamily({QString::fromUtf8("Comic Sans MS")});
        font1.setPointSize(12);
        font1.setBold(false);
        label_ack->setFont(font1);
        label_ack->setLayoutDirection(Qt::LeftToRight);
        label_ack->setLineWidth(1);
        label_ack->setMidLineWidth(0);
        label_ack->setTextFormat(Qt::PlainText);
        label_ack->setScaledContents(false);
        label_ack->setAlignment(Qt::AlignLeading | Qt::AlignLeft | Qt::AlignVCenter);
        label_ack->setWordWrap(false);
        label_ack->setMargin(0);
        label_ack->setIndent(-1);
        label_ack->setOpenExternalLinks(false);

        verticalLayout->addWidget(label_ack);

        pages->addWidget(page_main);
        page_size_selection = new QWidget();
        page_size_selection->setObjectName(QString::fromUtf8("page_size_selection"));
        verticalLayout_3 = new QVBoxLayout(page_size_selection);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        pages->addWidget(page_size_selection);

        verticalLayout_2->addWidget(pages);

        MenuWindow->setCentralWidget(centralwidget);

        retranslateUi(MenuWindow);

        pages->setCurrentIndex(0);

        QMetaObject::connectSlotsByName(MenuWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MenuWindow)
    {
        MenuWindow->setWindowTitle(QCoreApplication::translate("MenuWindow", "Simple Map", nullptr));
        label_simplemap->setText(QString());
        btn_load->setText(QString());
        label_ack->setText(QCoreApplication::translate("MenuWindow", "Code inspired by COM2012H PA4", nullptr));
    } // retranslateUi
};

namespace Ui
{
class MenuWindow : public Ui_MenuWindow
{
};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENUWINDOW_H
