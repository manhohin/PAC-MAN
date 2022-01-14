#ifndef GHOST_H
#define GHOST_H

#include "mainwindow.h"
#include <iostream>
#include "player.h"

class Ghost
{

public:
    enum class GhostStatus
    {
        UP = 1,
        DOWN = 2,
        LEFT = 3,
        RIGHT = 4
    };

    enum class GhostColor{
        BLUE = 1,
        ORANGE = 2,
        PINK = 3,
        RED = 4
    };

    Ghost(int x, int y, int speed, GhostStatus status, GhostColor color, Player *player_a, Player *player_b, Map *map);
    ~Ghost() = default;

    // get current position of the ghost
    int get_x();
    int get_y();
    GhostStatus get_status();
    GhostColor get_color();
    int get_speed();

    // set current position and status of the ghost
    void set_x(int x);
    void set_y(int y);
    void set_status(GhostStatus status);

    // return a random direction
    GhostStatus random_direction();
    int random_x();
    int random_y();

    // detect if there's any player that is on the same horizontal/veritical line with the ghost
    void detect_player(Player *player_a, Player * player_b,int a_x, int a_y, int b_x, int b_y);

    // when the ghost met the player, returns 0 if
    int met_player(int a_x, int a_y, int b_x, int b_y);

    // return true if there is an obstacle, else false
    bool detect_obstacle(GhostStatus status);

    // return true if the player is in spawn area
    bool detect_spawn_area();

    // the movement of the ghost
    void ghost_move(int seed);

    // let the ghost move out of the spawn area
    void ghost_move_out();


private:
    // the position, speed, and status of the ghost
    int x = 0;
    int y = 0;
    int speed = 1;
    GhostStatus status;
    GhostColor color;

    Player *player_a, *player_b;

    Map *map;

    bool color_reverse = true;

    bool scared = false;


};

#endif // GHOST_H
