#include "smalldots.h"
#include "map.h"
using namespace std;

Smalldots::Smalldots(Map &map) : powerup(map) {}
Smalldots::~Smalldots() {}

bool Smalldots::is_status_active() const { return status_active; }
void Smalldots::change_status_active() { status_active = !(is_status_active()); }
int Smalldots::get_x() const { return x; }
int Smalldots::get_y() const { return y; }

powerup::Type Smalldots::get_type() const { return Type::SMALLDOTS; }
