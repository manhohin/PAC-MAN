#include "winwidget.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QKeyEvent>
#include <QMessageBox>
#include <QPainter>
#include <QTextFormat>
#include <QWheelEvent>
#include <cmath>
#include <regex>
WinWidget::WinWidget(QWidget *parent) : QWidget(parent), winner(0) {}

WinWidget::~WinWidget() {}
void WinWidget::set_winner(int i) { winner = i; }
void WinWidget::paintEvent(QPaintEvent *event)
{
    QPainter paint{this};
    // Set black background
    paint.fillRect(0, 0, width(), height(), QBrush{QColor::fromRgb(0, 0, 0)});
    QFont ft;
    ft.setPixelSize(25);
    ft.setBold(true);
    ft.setFamily("Comic Sans MS");
    paint.setFont(ft);

#define STAT_WIDTH 500
#define HEIGHT 40
    // Draw score
    paint.setPen(Qt::white);
    switch (winner)
    {
    case 0:
        paint.drawText(350, 10 + HEIGHT, STAT_WIDTH, 50, Qt::AlignTop, "DRAW!");
        break;
    case 1:
        paint.drawText(300, 10 + HEIGHT, STAT_WIDTH, 50, Qt::AlignTop, "The Winner is P1!");
        break;
    case 2:
        paint.drawText(300, 10 + HEIGHT, STAT_WIDTH, 50, Qt::AlignTop, "The Winner is P2!");
        break;
    }
}
