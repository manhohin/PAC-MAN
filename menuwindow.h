#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include "map.h"

#include <QMainWindow>
#include <QMediaPlayer>

namespace Ui
{
class MenuWindow;
}

class MenuWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MenuWindow(QWidget *parent = nullptr);
    ~MenuWindow();

private slots:
    void on_btn_load_clicked();

private:
    void start_game(Map *map);
    QMediaPlayer *opening;
    Ui::MenuWindow *ui;

    // Store the grid size in this variable
    int selected_grid_size;
};

#endif // MENUWINDOW_H
