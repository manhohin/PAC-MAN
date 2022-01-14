#include "powerup.h"

powerup::powerup(Map &map) : Entities(map) {}

int powerup::get_time() const { return time; }

void powerup::set_buff_time() { buff_time = time; }

void powerup::change_buff_time()
{
    if (buff_time > 0)
    {
        buff_time--;
    }
}

Entities::Category powerup::get_category() const { return Entities::Category::POWERUP; }
