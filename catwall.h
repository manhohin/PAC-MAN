#ifndef CATWALL_H
#define CATWALL_H

#include "entities.h"
class catwall : public Entities
{
public:
    virtual Entities::Category get_category() const override;

protected:
    explicit catwall(Map &map);
};

#endif // CATWALL_H
