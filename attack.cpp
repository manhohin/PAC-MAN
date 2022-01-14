#include "attack.h"

attack::attack(Map &map) : powerup(map) {}

powerup::Type attack::get_type() const { return Type::ATTACK; }

bool attack::get_attack_status() const { return attack_status; }
