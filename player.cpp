#include "player.h"
#include <QDebug>
Player::Player(Map *const map, int id)
    : speed_up_time(0), slow_down_time(0), can_eat(false), can_eat_ghost(false), scorebuff_time(0), scorebuff(false),
      map(map), id(id), speed(2), score(0), status(PlayerStatus::UP)
{
    switch (id)
    {
    case 1:
        x = 0;
        y = 0;
        break;

    case 2:
        x = map->get_grid_x() - 1;
        y = 0;
    }
}

int Player::get_x() { return x; }

int Player::get_y() { return y; }

int Player::get_speed() { return speed; }

void Player::set_x(int num) { x = num; }

void Player::set_y(int num) { y = num; }

void Player::set_speed(int num) { speed = num; }

void Player::set_score(int num)
{
    if (scorebuff == true && num > 0)
    {
        score += num * scorebuff_multiplier;
    } else
    {
        score += num;
    }
}

int Player::get_score() { return score; }

Player::PlayerStatus Player::get_status() { return status; }

void Player::set_status(Player::PlayerStatus state)
{
    printf("test\n");
    status = state;
}

void Player::reset_cor()
{
    switch (id)
    {
    case 1:
        x = 0;
        y = 0;
        break;

    case 2:
        x = map->get_grid_x() - 1;
        y = 0;
    }
}

void Player::set_scorebuff()
{
    scorebuff = true;
    scorebuff_time = const_score_buff_time;
}

void Player::set_can_eat()
{
    can_eat = true;
    can_eat_time = const_can_eat_time;
}

void Player::set_can_eat_ghost()
{
    can_eat_ghost = true;
    can_eat_ghost_time = const_can_eat_ghost_time;
}

void Player::update_scorebuff()
{
    if (scorebuff_time > 0)
    {
        scorebuff_time--;
    } else if (scorebuff_time == 0)
    {
        scorebuff = false;
    }
}

void Player::update_can_eat()
{
    if (can_eat_time > 0)
    {
        can_eat_time--;
    } else if (can_eat_time == 0)
    {
        can_eat = false;
    }
}

void Player::update_can_eat_ghost()
{
    if (can_eat_ghost_time > 0)
    {
        can_eat_ghost_time--;
    } else if (can_eat_ghost_time == 0)
    {
        can_eat_ghost = false;
    }
}

void Player::update_all()
{
    update_scorebuff();
    update_can_eat();
    update_can_eat_ghost();
}
