/**
 * Do not modify
 */

#ifndef MAP_H
#define MAP_H

#include "attack.h"
#include "bigdots.h"
#include "catwall.h"
#include "entities.h"
#include "powerup.h"
#include "scorebuff.h"
#include "smalldots.h"
#include "speeddown.h"
#include "speedup.h"
#include "wall.h"
#include <ostream>
#include <string>

class Map
{
public:
    struct Coordinates
    {
        int x;
        int y;

        friend std::ostream &operator<<(std::ostream &output, const Coordinates &coordinates)
        {
            output << "(" << coordinates.x << "," << coordinates.y << ")";
            return output;
        }
    };

    explicit Map(const std::string filename);
    ~Map();

    // Return the maximum x and y coordinates of the map
    int get_grid_x() const;
    int get_grid_y() const;

    // To construct and destruct powerups
    Entities *get_at(const Coordinates &coordinates) const;
    bool is_empty_at(const Coordinates &coordinates) const;
    bool construct_at(Entities::Type type, const Coordinates &coordinates);
    bool demolish_at(const Coordinates &coordinates);

    inline Entities *get_at(int x, int y) const { return get_at(Coordinates{x, y}); };

    inline bool is_empty_at(int x, int y) const { return is_empty_at(Coordinates{x, y}); };

    inline bool construct_at(Entities::Type type, int x, int y) { return construct_at(type, Coordinates{x, y}); };

    inline bool demolish_at(int x, int y) { return demolish_at(Coordinates{x, y}); };

    // Generate powerups
    void gen_powerups(int type);

private:
    Entities ***grid;
    int grid_x;
    int grid_y;
    friend class Ghost;
};

#endif // MAP_H
