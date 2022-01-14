#ifndef POWERUP_H
#define POWERUP_H

#include "entities.h"
#include <string>

class powerup : public Entities
{
public:
    virtual ~powerup() = default;

    virtual Entities::Category get_category() const override;

    int get_time() const;

    // Set powerup time
    void set_buff_time();
    void change_buff_time();

protected:
    explicit powerup(Map &map);

    const int time = 7;
    int buff_time = 0;
};
#endif
