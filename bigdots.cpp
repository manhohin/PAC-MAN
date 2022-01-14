#include "bigdots.h"
#include "map.h"

using namespace std;

Bigdots::Bigdots(Map &map) : powerup(map) {}

Bigdots::~Bigdots() {}

bool Bigdots::is_status_active() const { return status_active; }
void Bigdots::change_status_active() { status_active = !(is_status_active()); }
bool Bigdots::is_eat_ghost_status_active() const { return eat_ghost_status_active; }
void Bigdots::change_eat_ghost_status_active() { eat_ghost_status_active = !(is_eat_ghost_status_active()); }
int Bigdots::get_x() const { return x; }
int Bigdots::get_y() const { return y; }
void Bigdots::set_buff_time() { time_left = time; }
void Bigdots::change_buff_time()
{
    if (time_left > 0)
    {
        time_left--;
    }
}

powerup::Type Bigdots::get_type() const { return Type::BIGDOTS; }
