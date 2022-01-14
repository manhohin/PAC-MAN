#ifndef ATTACK_H
#define ATTACK_H

#include "powerup.h"

class attack : public powerup
{
public:
    explicit attack(Map &map);

    virtual powerup::Type get_type() const override;

    bool get_attack_status() const;

protected:
    bool attack_status = true;
};

#endif
