#include "ghost.h"
#include "entities.h"
#include "graphics.h"
#include "mainwindow.h"
#include "player.h"

#include <QDebug>
#include <cmath>
#include <ctime>
#include <random>
#include <stdlib.h>

Ghost::Ghost(int x, int y, int speed, GhostStatus status, GhostColor color, Player *player_a, Player *player_b,
             Map *map)
    : x(x), y(y), speed(speed), status(status), color(color), player_a(player_a), player_b(player_b), map(map)
{
}

int Ghost::get_x() { return x; }
int Ghost::get_y() { return y; }

void Ghost::set_x(int x) { this->x = x; }
void Ghost::set_y(int y) { this->y = y; }

Ghost::GhostColor Ghost::get_color() { return this->color; }

Ghost::GhostStatus Ghost::get_status() { return status; }

int Ghost::get_speed() { return speed; }

void Ghost::set_status(Ghost::GhostStatus status) { this->status = status; }

void Ghost::detect_player(Player *player_a, Player *player_b, int a_x, int a_y, int b_x, int b_y)
{

    // when player_a, player-b and ghost are on the same line

    if (player_a->can_eat_ghost == true && player_b->can_eat_ghost == false)
    {
        if (std::abs(a_x - x) <= 4 && std::abs(b_x - x) <= 4 && a_y == y && b_y == y)
        {
            if (b_x > x && b_y == y)
            {
                if (detect_obstacle(GhostStatus::RIGHT) == false)
                {
                    status = GhostStatus::RIGHT;
                    x++;
                    return;
                }
            }
            if (b_x < x && b_y == y)
            {
                if (detect_obstacle(GhostStatus::LEFT) == false)
                {
                    status = GhostStatus::LEFT;
                    x--;
                    return;
                }
            }
            if (b_y < y && b_x == x)
            {
                if (detect_obstacle(GhostStatus::UP) == false)
                {
                    status = GhostStatus::UP;
                    y--;
                    return;
                }
            }
            if (b_y > y && b_x == x)
            {
                if (detect_obstacle(GhostStatus::DOWN) == false)
                {
                    status = GhostStatus::DOWN;
                    y++;
                    return;
                }
            }
        }
    }

    if (player_b->can_eat_ghost == true && player_a->can_eat_ghost == false)
    {
        if (std::abs(a_x - x) <= 4 && std::abs(b_x - x) <= 4 && a_y == y && b_y == y)
        {
            if (a_x > x && a_y == y)
            {
                if (detect_obstacle(GhostStatus::RIGHT) == false)
                {
                    status = GhostStatus::RIGHT;
                    x++;
                    return;
                }
            }
            if (a_x < x && a_y == y)
            {
                if (detect_obstacle(GhostStatus::LEFT) == false)
                {
                    status = GhostStatus::LEFT;
                    x--;
                    return;
                }
            }
            if (a_y < y && a_x == x)
            {
                if (detect_obstacle(GhostStatus::UP) == false)
                {
                    status = GhostStatus::UP;
                    y--;
                    return;
                }
            }
            if (a_y > y && a_x == x)
            {
                if (detect_obstacle(GhostStatus::DOWN) == false)
                {
                    status = GhostStatus::DOWN;
                    y++;
                    return;
                }
            }
        }
    }

    if (player_a->can_eat_ghost == false && player_b->can_eat_ghost == false)
        return;

    if (player_a->can_eat_ghost == true && player_b->can_eat_ghost == true)
    {
        if (std::abs(a_x - x) <= 4 && std::abs(b_x - x) <= 4 && a_y == y && b_y == y)
        {
            if (detect_obstacle(GhostStatus::UP) == false)
            {
                status = GhostStatus::UP;
                y--;
                return;
            }
            if (detect_obstacle(GhostStatus::DOWN) == false)
            {
                status = GhostStatus::DOWN;
                y++;
                return;
            }
            return;
        }
    }

    if (player_a->can_eat_ghost == true)
    {
        if (std::abs(a_x - x) <= 4 && a_y == y)
        {
            if (a_x > x && status == GhostStatus::LEFT)
                if (detect_obstacle(GhostStatus::RIGHT) == false)
                {
                    status = GhostStatus::RIGHT;
                    x++;
                    return;
                }
            if (a_x < x && status == GhostStatus::RIGHT)
                if (detect_obstacle(GhostStatus::LEFT) == false)
                {
                    status = GhostStatus::LEFT;
                    x--;
                    return;
                }
        }

        if (std::abs(a_y - y) <= 4 && a_x == x)
        {
            qDebug() << "vertical";
            if (a_y < y && status == GhostStatus::UP)
                if (detect_obstacle(GhostStatus::DOWN) == false)
                {
                    status = GhostStatus::DOWN;
                    y++;
                }
            if (a_y > y && status == GhostStatus::DOWN)
                if (detect_obstacle(GhostStatus::UP) == false)
                {
                    status = GhostStatus::UP;
                    y--;
                }
        }
    } else
    {
        if (std::abs(a_x - x) <= 4 && a_y == y)
        {
            if (a_x > x)
            {
                if (detect_obstacle(GhostStatus::RIGHT) == false)
                {
                    status = GhostStatus::RIGHT;
                    x++;
                    return;
                }
            }
            if (a_x < x)
            {
                if (detect_obstacle(GhostStatus::LEFT) == false)
                {
                    status = GhostStatus::LEFT;
                    x--;
                    return;
                }
            }
        }

        if (std::abs(a_y - y) <= 4 && a_x == x)
        {
            if (a_y < y && a_x == x)
            {
                if (detect_obstacle(GhostStatus::UP) == false)
                {
                    status = GhostStatus::UP;
                    y--;
                    return;
                }
            }
            if (a_y > y && a_x == x)
            {
                if (detect_obstacle(GhostStatus::DOWN) == false)
                {
                    status = GhostStatus::DOWN;
                    y++;
                    return;
                }
            }
        }
    }

    if (player_b->can_eat_ghost == true)
    {
        if (std::abs(b_x - x) <= 4 && b_y == y)
        {
            if (b_x > x && status == GhostStatus::LEFT)
                if (detect_obstacle(GhostStatus::RIGHT) == false)
                {
                    status = GhostStatus::RIGHT;
                    x++;
                    return;
                }
            if (b_x < x && status == GhostStatus::RIGHT)
                if (detect_obstacle(GhostStatus::LEFT) == false)
                {
                    status = GhostStatus::LEFT;
                    x--;
                    return;
                }
        }

        if (std::abs(b_y - y) <= 4 && b_x == x)
        {
            qDebug() << "vertical";
            if (b_y < y && status == GhostStatus::UP)
                if (detect_obstacle(GhostStatus::DOWN) == false)
                {
                    status = GhostStatus::DOWN;
                    y++;
                }
            if (b_y > y && status == GhostStatus::DOWN)
                if (detect_obstacle(GhostStatus::UP) == false)
                {
                    status = GhostStatus::UP;
                    y--;
                }
        }
    } else
    {
        if (std::abs(b_x - x) <= 4 && b_y == y)
        {
            if (b_x > x)
            {
                if (detect_obstacle(GhostStatus::RIGHT) == false)
                {
                    status = GhostStatus::RIGHT;
                    x++;
                    return;
                }
            }
            if (b_x < x)
            {
                if (detect_obstacle(GhostStatus::LEFT) == false)
                {
                    status = GhostStatus::LEFT;
                    x--;
                    return;
                }
            }
        }

        if (std::abs(b_y - y) <= 4 && b_x == x)
        {
            if (b_y < y && b_x == x)
            {
                if (detect_obstacle(GhostStatus::UP) == false)
                {
                    status = GhostStatus::UP;
                    y--;
                    return;
                }
            }
            if (b_y > y && b_x == x)
            {
                if (detect_obstacle(GhostStatus::DOWN) == false)
                {
                    status = GhostStatus::DOWN;
                    y++;
                    return;
                }
            }
        }
    }
}

// returns
// 0 if not met
// 1 if player_a can eat the ghost
// 2 if ghost can eat the player_a
// 3 if player_b can eat the ghost
// 4 if ghost can eat player_b

int Ghost::met_player(int a_x, int a_y, int b_x, int b_y)
{

    // if ghost meets player a
    if (x == a_x && y == a_y)
    {
        if (player_a->can_eat_ghost == true)
            return 1;
        else
            return 2;
    }

    // if ghost meets player b
    if (x == b_x && y == b_y)
    {
        if (player_b->can_eat_ghost == true)
            return 3;
        else
            return 4;
    }
    return 0;
}

bool Ghost::detect_obstacle(GhostStatus status)
{
    switch (status)
    {
    case Ghost::GhostStatus::UP:
        if (y - 1 < 0)
            return true; // detect border
        if (map->grid[x][y - 1] != nullptr && map->grid[x][y - 1]->get_type() == Entities::Type::WALL)
            return true; // detect walls
        if (y > 15 && y - 1 <= 15 && x >= 9 && x <= 16)
            return true; // detect spawn area

        break;
    case Ghost::GhostStatus::DOWN:
        if (y + 1 >= 29)
            return true; // detect border
        if (map->grid[x][y + 1] != nullptr && map->grid[x][y + 1]->get_type() == Entities::Type::WALL)
            return true; // detect walls
        if (y < 11 && y + 1 >= 11 && x >= 9 && x <= 16)
            return true; // detect spawn area

        break;
    case Ghost::GhostStatus::LEFT:
        if (x - 1 < 0)
            return true; // detect border
        if (map->grid[x - 1][y] != nullptr && map->grid[x - 1][y]->get_type() == Entities::Type::WALL)
            return true; // detect walls
        if (x > 16 && x - 1 <= 16 && y >= 11 && y <= 15)
            return true; // detect spawn area

        break;
    case Ghost::GhostStatus::RIGHT:
        if (x + 1 >= 26)
            return true; // detect border
        if (map->grid[x + 1][y] != nullptr && map->grid[x + 1][y]->get_type() == Entities::Type::WALL)
            return true; // detect walls
        if (x < 9 && x + 1 >= 9 && y >= 11 && y <= 15)
            return true; // detect spawn area

        break;
    }
    return false;
}

bool Ghost::detect_spawn_area()
{
    if (x <= 16 && x >= 9 && y <= 15 && y >= 11)
        return true;
    return false;
}

void Ghost::ghost_move(int seed)
{

    // count the number of possible ways to go
    int count = 0;
    int directions[4] = {-1, -1, -1, -1};

    // regular case detection
    if (detect_obstacle(GhostStatus::UP) == false && status != GhostStatus::DOWN)
    {
        //        qDebug()<<"up";
        directions[count] = 0;
        count++;
    }
    if (detect_obstacle(GhostStatus::DOWN) == false && status != GhostStatus::UP)
    {
        //        qDebug()<<"down";
        directions[count] = 1;
        count++;
    }
    if (detect_obstacle(GhostStatus::LEFT) == false && status != GhostStatus::RIGHT)
    {
        //        qDebug()<<"left";
        directions[count] = 2;
        count++;
    }
    if (detect_obstacle(GhostStatus::RIGHT) == false && status != GhostStatus::LEFT)
    {
        //        qDebug()<<"right";
        directions[count] = 3;
        count++;
    }

    if (count == 0)
    {
        switch (status)
        {
        case GhostStatus::UP:
            if (y - 1 < 0)
            {
                set_status(GhostStatus::DOWN);
                y++;
            }
            return;
        case GhostStatus::DOWN:
            if (y + 1 >= 29)
            {
                set_status(GhostStatus::UP);
                y--;
            }
            return;
        case GhostStatus::LEFT:
            if (x - 1 < 0)
            {
                set_status(GhostStatus::RIGHT);
                x++;
            }
            return;
        case GhostStatus::RIGHT:
            if (x + 1 >= 26)
            {
                set_status(GhostStatus::LEFT);
                x--;
            }
            return;
        }
    }

    // only one direction to go
    if (count == 1)
    {
        switch (directions[0])
        {
        case 0:
            set_status(GhostStatus::UP);
            y--;
            return;
        case 1:
            set_status(GhostStatus::DOWN);
            y++;
            return;
        case 2:
            set_status(GhostStatus::LEFT);
            x--;
            return;
        case 3:
            set_status(GhostStatus::RIGHT);
            x++;
            return;
        }
        return;
    }

    // two directions to go
    if (count == 2)
    {
        // int random_num = rand()%2;
        //        std::random_device rd;
        std::mt19937 gen(seed);
        std::uniform_int_distribution<int> dis(0, 3);
        int random_num = dis(gen);
        switch (directions[random_num])
        {
        case 0:
            set_status(GhostStatus::UP);
            y--;
            return;
        case 1:
            set_status(GhostStatus::DOWN);
            y++;
            return;
        case 2:
            set_status(GhostStatus::LEFT);
            x--;
            return;
        case 3:
            set_status(GhostStatus::RIGHT);
            x++;
            return;
        }
    }

    // 3 directions to go
    if (count == 3)
    {
        // int random_num = rand()%3;
        std::random_device rd;
        std::mt19937 gen(seed);
        std::uniform_int_distribution<int> dis(0, 3);
        int random_num = dis(gen);
        switch (directions[random_num])
        {
        case 0:
            set_status(GhostStatus::UP);
            y--;
            return;
        case 1:
            set_status(GhostStatus::DOWN);
            y++;
            return;
        case 2:
            set_status(GhostStatus::LEFT);
            x--;
            return;
        case 3:
            set_status(GhostStatus::RIGHT);
            x++;
            return;
        }
    }

    // 4 directions to go
    if (count == 3)
    {
        // int random_num = rand()%4;
        //        std::random_device rd;
        std::mt19937 gen(seed);
        std::uniform_int_distribution<int> dis(0, 3);
        int random_num = dis(gen);
        switch (directions[random_num])
        {
        case 0:
            set_status(GhostStatus::UP);
            y--;
            return;
        case 1:
            set_status(GhostStatus::DOWN);
            y++;
            return;
        case 2:
            set_status(GhostStatus::LEFT);
            x--;
            return;
        case 3:
            set_status(GhostStatus::RIGHT);
            x++;
            return;
        }
    }
}

int Ghost::random_x()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(10, 15);
    int random_num = dis(gen);
    return random_num;
}

int Ghost::random_y()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(12, 14);
    int random_num = dis(gen);
    return random_num;
}

void Ghost::ghost_move_out()
{
    // if(x <= 9 || x >=16 || y >=15 || y <= 11) return;
    if (x > 13)
    {
        set_status(GhostStatus::LEFT);
        x--;
    } else if (x < 13)
    {
        set_status(GhostStatus::RIGHT);
        x++;
    } else if (x == 13)
    {
        if (y > 10)
        {
            set_status(GhostStatus::UP);
            y--;
        }
    }
}

Ghost::GhostStatus Ghost::random_direction()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(1, 4);
    int random_num = dis(gen);
    if (random_num == 1)
        return Ghost::GhostStatus::UP;
    if (random_num == 2)
        return Ghost::GhostStatus::DOWN;
    if (random_num == 3)
        return Ghost::GhostStatus::LEFT;
    if (random_num == 4)
        return Ghost::GhostStatus::RIGHT;
    return Ghost::GhostStatus::UP;
}
