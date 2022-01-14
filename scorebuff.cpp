#include "scorebuff.h"

scorebuff::scorebuff(Map &map) : powerup(map) {}

powerup::Type scorebuff::get_type() const { return Type::SCOREBUFF; }

int scorebuff::get_scoreb() const { return scoreb; }
