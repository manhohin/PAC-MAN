#ifndef PLAYER_H
#define PLAYER_H

#include "map.h"

class Player
{
public:
    explicit Player(Map *const map, int id);
    ~Player();
    enum class PlayerStatus
    {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };
    // Duration of each powerups and determine if the powerup effect is true
    int speed_up_time;
    int slow_down_time;
    bool can_eat;
    bool can_eat_ghost;
    // modify the scorebuff time
    const int const_score_buff_time = 70;
    int scorebuff_time;
    bool scorebuff;
    // modify the scorebuff effect
    const int scorebuff_multiplier = 2;
    // modify the can eat time
    const int const_can_eat_time = 70;
    int can_eat_time;
    // modify the can eat ghost time
    const int const_can_eat_ghost_time = 70;
    int can_eat_ghost_time;

    // Return basic information of the player
    int get_x();
    int get_y();
    int get_speed();

    // Changing the elements of the player
    void set_x(int num);
    void set_y(int num);

    // smaller number of speed = faster
    void set_speed(int num);
    void set_score(int num);

    // Return score of the player
    int get_score();

    // Return the direction of the player
    Player::PlayerStatus get_status();

    // Change the direction of the player
    void set_status(Player::PlayerStatus state);

    // Send the player back to it's original position
    void reset_cor();

    // Set the powerup status
    void set_scorebuff();
    void set_can_eat();
    void set_can_eat_ghost();
    void update_scorebuff();
    void update_can_eat();
    void update_can_eat_ghost();
    void update_all();

private:
    Map *const map;
    int id;
    int x;
    int y;
    int speed;
    int score;
    PlayerStatus status;
};

#endif // PLAYER_H
