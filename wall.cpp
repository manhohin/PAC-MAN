#include "wall.h"
#include <QDebug>

wall::wall(Map &map) : catwall(map) {}

Entities::Type wall::get_type() const { return Type::WALL; }
