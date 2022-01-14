#include "speeddown.h"

speeddown::speeddown(Map &map) : powerup(map) {}

powerup::Type speeddown::get_type() const { return Type::SPEEDDOWN; }

int speeddown::get_speedup() const { return speed_decrease; }
