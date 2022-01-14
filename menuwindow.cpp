#include "menuwindow.h"
#include "mainwindow.h"
#include "map.h"
#include "ui_menuwindow.h"

#include <QFileDialog>
#include <QMediaPlaylist>
#include <QPixmap>

MenuWindow::MenuWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MenuWindow), selected_grid_size(20)
{
    ui->setupUi(this);
    this->ui->pages->setCurrentIndex(0);

    QMediaPlaylist *playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/sounds/sounds/pacman_beginning.wav"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    opening = new QMediaPlayer();
    opening->setPlaylist(playlist);
    opening->play();
}

MenuWindow::~MenuWindow() { delete ui; }

void MenuWindow::start_game(Map *map)
{
    MainWindow *m = new MainWindow{map, nullptr};
    m->setAttribute(Qt::WA_DeleteOnClose);
    m->show();
    close();
}

void MenuWindow::on_btn_load_clicked()
{
    start_game(new Map{"map.txt"});
    opening->stop();
}
