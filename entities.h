#ifndef ENTITIES_H
#define ENTITIES_H

#include <string>

class Map;

class Entities
{
public:
    enum class Type
    {
        WALL = 1,
        SPEEDUP = 2,
        SPEEDDOWN = 3,
        SCOREBUFF = 4,
        ATTACK = 5,
        SMALLDOTS = 6,
        BIGDOTS = 7
    };

    enum class Category
    {
        CATWALL,
        POWERUP
    };
    virtual ~Entities() = default;
    virtual Entities::Type get_type() const = 0;
    virtual Entities::Category get_category() const = 0;

protected:
    explicit Entities(Map &map);

    Map &map;
};

#endif // ENTITIES_H
