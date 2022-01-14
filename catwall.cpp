#include "catwall.h"

catwall::catwall(Map &map) : Entities(map) {}

Entities::Category catwall::get_category() const { return Category::CATWALL; }
