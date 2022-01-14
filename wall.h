#ifndef WALL_H
#define WALL_H

#include "catwall.h"
class wall : public catwall
{
public:
    explicit wall(Map &map);
    virtual Entities::Type get_type() const override;
};

#endif // WALL_H
