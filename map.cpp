#include "map.h"
#include <QDebug>
#include <fstream>
using namespace std;

Map::Map(const std::string filename) : grid_x(26), grid_y(29)
{
    ifstream input;
    input.open(filename);
    grid = new Entities **[grid_x];
    for (int x = 0; x < grid_x; x++)
    {
        grid[x] = new Entities *[grid_y];
        for (int y = 0; y < grid_y; y++)
        {
            int type;
            input >> type;
            if (type >= 1 && type <= 7)
            {
                switch (static_cast<Entities::Type>(type))
                {
                case Entities::Type::WALL:
                    grid[x][y] = new wall{*this};
                    break;
                case Entities::Type::SPEEDUP:
                    grid[x][y] = new speedup{*this};
                    break;
                case Entities::Type::SPEEDDOWN:
                    grid[x][y] = new speeddown{*this};
                    break;
                case Entities::Type::SCOREBUFF:
                    grid[x][y] = new scorebuff{*this};
                    break;
                case Entities::Type::ATTACK:
                {
                    grid[x][y] = new attack{*this};
                    break;
                }
                case Entities::Type::SMALLDOTS:
                {
                    grid[x][y] = new Smalldots{*this};
                    break;
                }
                case Entities::Type::BIGDOTS:
                {
                    grid[x][y] = new Bigdots{*this};
                    break;
                }
                }
            } else
            {
                grid[x][y] = nullptr;
            }
        }
    }

    input.close();
    srand((unsigned)time(0));
    for (int i = 0; i < 3; i++)
    {
        int type = rand() % (5 - 2 + 1) + 2;
        gen_powerups(type);
    }
    for (int x = 0; x < grid_x; x++)
    {
        for (int y = 0; y < grid_y; y++)
        {
            if ((grid[x][y] == nullptr) && !((x >= 9 && x <= 16) && (y >= 11 && y <= 15)))
            {
                construct_at(Entities::Type::SMALLDOTS, x, y);
            }
        }
    }
}

void Map::gen_powerups(int type)
{
    srand((unsigned)time(0));

    int rand_x = (rand() % (grid_x - 1));
    int rand_y = (rand() % (grid_y - 1));
    while ((grid[rand_x][rand_y] != nullptr) || ((rand_x >= 9 && rand_x <= 16) && (rand_y >= 11 && rand_y <= 15)))
    {
        rand_x = (rand() % (grid_x - 1));
        rand_y = (rand() % (grid_y - 1));
    }
    switch (type)
    {
    case 2:
        construct_at(Entities::Type::SPEEDUP, rand_x, rand_y);
        break;
    case 3:
        construct_at(Entities::Type::SPEEDDOWN, rand_x, rand_y);
        break;
    case 4:
        construct_at(Entities::Type::SCOREBUFF, rand_x, rand_y);
        break;
    case 5:
        construct_at(Entities::Type::ATTACK, rand_x, rand_y);
        break;
    }
}

Map::~Map()
{
    for (int x = 0; x < grid_x; x++)
    {
        for (int y = 0; y < grid_y; y++)
        {
            delete grid[x][y];
        }
        delete[] grid[x];
    }
    delete[] grid;
}

int Map::get_grid_x() const { return grid_x; }

int Map::get_grid_y() const { return grid_y; }
Entities *Map::get_at(const Coordinates &coordinates) const
{
    if (coordinates.x < 0 || coordinates.x >= grid_x)
        return nullptr;
    if (coordinates.y < 0 || coordinates.y >= grid_y)
        return nullptr;
    return grid[coordinates.x][coordinates.y];
}

bool Map::is_empty_at(const Coordinates &coordinates) const
{
    if (coordinates.x < 0 || coordinates.x >= grid_x)
        return false;
    if (coordinates.y < 0 || coordinates.y >= grid_y)
        return false;

    return get_at(coordinates) == nullptr;
}

bool Map::construct_at(Entities::Type type, const Coordinates &coordinates)
{

    Entities *entities;
    switch (type)
    {
    case Entities::Type::WALL:
        entities = new wall{*this};
        break;
    case Entities::Type::SPEEDUP:
        entities = new speedup{*this};
        break;
    case Entities::Type::SPEEDDOWN:
        entities = new speeddown{*this};
        break;
    case Entities::Type::SCOREBUFF:
        entities = new scorebuff{*this};
        break;
    case Entities::Type::ATTACK:
        entities = new attack{*this};
        break;
    case Entities::Type::SMALLDOTS:
        entities = new Smalldots{*this};
        break;
    case Entities::Type::BIGDOTS:
        entities = new Bigdots{*this};
        break;
    }

    grid[coordinates.x][coordinates.y] = entities;

    return true;
}

bool Map::demolish_at(const Coordinates &coordinates)
{
    if (coordinates.x < 0 || coordinates.x >= grid_x)
        return false;
    if (coordinates.y < 0 || coordinates.y >= grid_y)
        return false;

    if (grid[coordinates.x][coordinates.y] == nullptr)
        return false;

    Entities *entities = grid[coordinates.x][coordinates.y];

    delete entities;
    grid[coordinates.x][coordinates.y] = nullptr;

    return true;
}
