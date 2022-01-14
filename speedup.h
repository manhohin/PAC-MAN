#ifndef SPEEDUP_H
#define SPEEDUP_H

#include "powerup.h"

class speedup : public powerup
{
public:
    virtual powerup::Type get_type() const override;

    int get_speedup() const;

    explicit speedup(Map &map);

protected:
    double speed_increase = 0.5; // multiply to the player speed
};

#endif
