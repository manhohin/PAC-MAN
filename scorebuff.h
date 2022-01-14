#ifndef SCOREBUFF_H
#define SCOREBUFF_H

#include "powerup.h"

class scorebuff : public powerup
{
public:
    virtual powerup::Type get_type() const override;

    int get_scoreb() const;

    explicit scorebuff(Map &map);

protected:
    double scoreb = 1.5;
};

#endif
