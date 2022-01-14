#ifndef SPEEDDOWN_H
#define SPEEDDOWN_H

#include "powerup.h"

class speeddown : public powerup
{
public:
    virtual powerup::Type get_type() const override;

    int get_speedup() const;

    explicit speeddown(Map &map);

protected:
    double speed_decrease = 1.5; // multiply to the player speed
};

#endif
