#include "winwindow.h"
#include "ui_winwindow.h"

WinWindow::WinWindow(int player, QWidget *parent) : QMainWindow(parent), ui(new Ui::WinWindow), player(player)
{

    ui->setupUi(this);
    ui->centralwidget->set_winner(player);
}

WinWindow::~WinWindow() { delete ui; }
