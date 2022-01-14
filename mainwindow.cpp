#include "mainwindow.h"
#include "map.h"
#include "ui_mainwindow.h"
#include "winwindow.h"

#include <QFileDialog>
#include <QMainWindow>
#include <QString>
#include <QTimer>

MainWindow::MainWindow(Map *const map, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), map(map), selected_side_menu_button(SideMenuButton::NAVIGATE),
      selected_overlay_button(OverlayButton::NORMAL), side_menu_status(SideMenuStatus::HIDDEN)
{
    ui->setupUi(this);

    // Run main loop
    loop_timer = new QTimer{this};
    connect(loop_timer, &QTimer::timeout, this, &MainWindow::main_loop);
    // 5 updates per second
    loop_timer->start(200);
}

MainWindow::~MainWindow()
{
    delete ui;
    loop_timer->stop();
    delete loop_timer;
    delete map;
}

// This is called 5 times per second
void MainWindow::main_loop()
{
    if (ui->widget->smalldot_num <= 0)
    {
        WinWindow *w = new WinWindow(ui->widget->return_winner());
        w->setAttribute(Qt::WA_DeleteOnClose);
        w->show();
        close();
    }
    ui->widget->loop();
}
