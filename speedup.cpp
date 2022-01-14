#include "speedup.h"

speedup::speedup(Map &map) : powerup(map) {}

powerup::Type speedup::get_type() const { return Type::SPEEDUP; }

int speedup::get_speedup() const { return speed_increase; }
