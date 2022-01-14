#ifndef BIGDOTS_H
#define BIGDOTS_H

#include "entities.h"
#include "map.h"
#include "powerup.h"
#include <iostream>

class Bigdots : public powerup
{
public:
    int x;
    int y;
    bool status_active = true;            // bigdot alive or consumed?
    bool eat_ghost_status_active = false; // whether player can eat ghost

    const int time = 70;
    int time_left = 70;

    explicit Bigdots(Map &map);
    ~Bigdots();

    bool is_status_active() const;
    void change_status_active();

    bool is_eat_ghost_status_active() const;
    void change_eat_ghost_status_active();

    int get_x() const;
    int get_y() const;

    void set_buff_time();
    void change_buff_time();

    virtual powerup::Type get_type() const override;
};
#endif // BIGDOTS_H
