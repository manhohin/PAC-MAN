#ifndef SMALLDOTS_H
#define SMALLDOTS_H

#include "bigdots.h"
#include "entities.h"
#include "map.h"
#include "powerup.h"
#include <iostream>

class Smalldots : public powerup
{
public:
    bool status_active = true; // still alive?

    explicit Smalldots(Map &map);
    ~Smalldots();

    bool is_status_active() const;
    void change_status_active();
    int get_x() const;
    int get_y() const;

    virtual powerup::Type get_type() const override;

private:
    int x;
    int y;
};
#endif
