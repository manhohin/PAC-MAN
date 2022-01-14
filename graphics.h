/**
* Utilities for graphics and display
*/

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "map.h"
#include "mainwindow.h"
#include "player.h"
#include "ghost.h"

#include <QPixmap>
#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>

class GameWidget: public QWidget {
public:
    GameWidget(QWidget* parent = nullptr);
    QMediaPlaylist *playlist_bgm;
    QMediaPlayer *background_music;
    QMediaPlayer *chomp;

    QMediaPlayer *player_die;
    QMediaPlayer *ghost_die;

    QMediaPlaylist *playlist_can_eat_ghost;
    QMediaPlayer *background_can_eat_ghost;

    ~GameWidget();

    GameWidget(const GameWidget&) = delete;
    GameWidget& operator=(const GameWidget&) = delete;
    int return_winner();
    int smalldot_num;

    // Loop, called by main_loop() in MainWindow
    void loop();

    //animation index
    int player_animation;
    bool player_animation_reverse;
    bool player_switch_color;

    //eat determination
    void player_eat_player_determinaion();
    // detect if ghost meets player; refer to ghost.cpp for the description of met_player function
    void ghost_eat_player_determination();


protected:
    // Handle drawing
    virtual void paintEvent(QPaintEvent* event) override;

    // Handle WASD keys and Arrow keys for player movement
    virtual void keyPressEvent(QKeyEvent* event) override;

    // Handle mouse scrolling for magnification
    virtual void wheelEvent(QWheelEvent* event) override;

private:
    // Obtain the display coordinates from the 'real' coordinates
    void to_display_coordinates(int x, int y, int& dispx, int& dispy);

    // Obtain the 'real' coordinates from the display coordinates
    void to_real_coordinates(int dispx, int dispy, int& x, int& y);

    // Obtain the coordinates of the grid (2D array index) from display coordinates
    void obtain_grid_coordinates(int dispx, int dispy, int& x, int& y);

    // Obtain the coordinates of the grid (2D array index) from real coordinates
    void obtain_grid_coordinates_from_real(int rx, int ry, int& x, int& y);

    /******** THE GHOST PART ********/
    // Return a random x-coordinate for the ghost spawn point between 9-16
    int random_x();

    // Return a random y-coordinate for the ghost spawn point between 11-15
    int random_y();

    // Return a random direction for the ghost
    Ghost::GhostStatus random_direction();

    // Reset player a's position after eaten by the ghost
    void reset_player_a();

    // Reset player b's position after eaten by the ghost
    void reset_player_b();

    /******** THE END OF THE GHOST PART ********/

    void drawLine(QPainter& paint, int x1, int y1, int x2, int y2);
    void drawPixmap(QPainter& paint, int x, int y, int w, int h, const QPixmap&);
    void fillRect(QPainter& paint, int x, int y, int w, int h, const QBrush&);

    // Load and unload icons
    void load_icons();
    void dealloc_icons();

    Map *const map;
    int grid_x;
    int grid_y;

    Player *player_a, *player_b;

    Ghost *ghost_b, *ghost_o, *ghost_p, *ghost_r;

    // Scrolling
    int scroll_x, scroll_y;
    // Magnification
    float scale;

    // Keys pressed
    bool UP, DOWN, LEFT, RIGHT;

    int tick; // Map ticks (number of calls of loop function) elapsed since the beginning of the program


    // The coordinates of the grid on of the players
    int a_grid_x;
    int a_grid_y;
    int b_grid_x;
    int b_grid_y;

    // Icons sorted according to the enum Entities
    QPixmap* ICONS;
    QPixmap* PLAYER_A_ICONS;
    QPixmap* PLAYER_B_ICONS;
    QPixmap* PLAYER_SCARED_ICONS;
    QPixmap** GHOSTS_ICONS;
    QPixmap** GHOSTS_SCARED_ICONS;


};

#endif // GRAPHICS_H
