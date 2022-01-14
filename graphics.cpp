#include "graphics.h"
#include "map.h"
#include "mainwindow.h"

#include <QPainter>
#include <QKeyEvent>
#include <QWheelEvent>
#include <QMessageBox>
#include <QTextFormat>
#include <QDebug>
#include <cmath>
#include <regex>
#include <random>

GameWidget::GameWidget(QWidget* parent):
    QWidget(parent),
    smalldot_num(0),
    player_animation(0),
    player_animation_reverse(false),
    player_switch_color(false),
    map(dynamic_cast<MainWindow *>(parent)->map),
    grid_x(map->get_grid_x()),
    grid_y(map->get_grid_y()),
    player_a(new Player{map, 1}),
    player_b(new Player{map, 2}),
    ghost_b(new Ghost{random_x(),random_y(), 2, random_direction(), Ghost::GhostColor::BLUE, player_a, player_b, map}),
    ghost_o(new Ghost{random_x(),random_y(), 2, random_direction(), Ghost::GhostColor::ORANGE, player_a, player_b, map}),
    ghost_p(new Ghost{random_x(),random_y(), 2, random_direction(), Ghost::GhostColor::PINK, player_a, player_b, map}),
    ghost_r(new Ghost{random_x(),random_y(), 2, random_direction(), Ghost::GhostColor::RED, player_a, player_b, map}),
    scroll_x(0), scroll_y(0),
    scale(0.25f),
    UP(false), DOWN(false), LEFT(false), RIGHT(false),
    tick(0),
    a_grid_x(player_a->get_x()), a_grid_y(player_a->get_y()),
    b_grid_x(player_b->get_x()), b_grid_y(player_b->get_y())
{
    for(int x=0; x<=map->get_grid_x(); x++){
        for(int y=0; y<=map->get_grid_y();y ++){
            if(map->get_at(x,y)!=nullptr){
                if(map->get_at(x,y)->get_type()==Entities::Type::SMALLDOTS){
                    smalldot_num=smalldot_num+1;
                }
            }

        }
    }
    load_icons();
    setMouseTracking(true);
    grabKeyboard();


    playlist_bgm = new QMediaPlaylist();
    playlist_bgm->addMedia(QUrl("qrc:/sounds/sounds/background.mp3"));
    playlist_bgm->setPlaybackMode(QMediaPlaylist::Loop);
    background_music = new QMediaPlayer();
    background_music->setPlaylist(playlist_bgm);
    background_music->play();

    chomp = new QMediaPlayer();
    chomp->setMedia(QUrl("qrc:/sounds/sounds/pacman_chomp.mp3"));
    player_die = new QMediaPlayer();
    player_die->setMedia(QUrl("qrc:/sounds/sounds/pacman_death.wav"));
    ghost_die = new QMediaPlayer();
    ghost_die->setMedia(QUrl("qrc:/sounds/sounds/pacman_eatghost.wav"));

    playlist_can_eat_ghost = new QMediaPlaylist();
    playlist_can_eat_ghost->addMedia(QUrl("qrc:/sounds/sounds/eat_ghost_time.mp3"));
    playlist_can_eat_ghost->setPlaybackMode(QMediaPlaylist::Loop);
    background_can_eat_ghost = new QMediaPlayer();
    background_can_eat_ghost->setPlaylist(playlist_can_eat_ghost);
}

GameWidget::~GameWidget() {
    dealloc_icons();
}

void GameWidget::loop() {
    //Move player a
    if(tick%player_a->get_speed()==0){
        switch(player_a->get_status()){
            case Player::PlayerStatus::UP:
                if(a_grid_y>0){
                    if(map->get_at(a_grid_x, a_grid_y-1)!=nullptr){
                        if(map->get_at(a_grid_x, a_grid_y-1)->get_type()==Entities::Type::WALL){
                            a_grid_y=a_grid_y;
                        }else{
                            a_grid_y=a_grid_y-1;
                        }
                    }else{
                        a_grid_y=a_grid_y-1;
                    }

                }else{
                    if(map->get_at(a_grid_x, grid_y-1)!=nullptr){
                        if(map->get_at(a_grid_x, grid_y-1)->get_type()==Entities::Type::WALL){
                            a_grid_y=a_grid_y;
                        }else{
                            a_grid_y=grid_y-1;
                        }
                    }else{
                        a_grid_y=grid_y-1;
                    }
                }
                player_a->set_y(a_grid_y);
            break;
            case Player::PlayerStatus::DOWN:
                if(a_grid_y<grid_y-1){
                    if(map->get_at(a_grid_x, a_grid_y+1)!=nullptr){
                        if(map->get_at(a_grid_x, a_grid_y+1)->get_type()==Entities::Type::WALL){
                            a_grid_y=a_grid_y;
                        }else{
                            a_grid_y=a_grid_y+1;
                        }
                    }else{
                        a_grid_y=a_grid_y+1;
                    }

                }else{
                    if(map->get_at(a_grid_x, 0)!=nullptr){
                        if(map->get_at(a_grid_x, 0)->get_type()==Entities::Type::WALL){
                            a_grid_y=a_grid_y;
                        }else{
                            a_grid_y=0;
                        }
                    }else{
                        a_grid_y=0;
                    }
                }
                    player_a->set_y(a_grid_y);
            break;
            case Player::PlayerStatus::LEFT:
                if(a_grid_x>0){
                    if(map->get_at(a_grid_x-1, a_grid_y)!=nullptr){
                        if(map->get_at(a_grid_x-1, a_grid_y)->get_type()==Entities::Type::WALL){
                           a_grid_x=a_grid_x;
                        }else{
                            a_grid_x=a_grid_x-1;
                        }
                    }else{
                        a_grid_x=a_grid_x-1;
                    }
                }else{
                    if(map->get_at(grid_x-1, a_grid_y)!=nullptr){
                        if(map->get_at(grid_x-1, a_grid_y)->get_type()==Entities::Type::WALL){
                           a_grid_x=a_grid_x;
                        }else{
                            a_grid_x=grid_x-1;
                        }
                    }else{
                        a_grid_x=grid_x-1;
                    }
                }
                player_a->set_x(a_grid_x);
            break;
            case Player::PlayerStatus::RIGHT:
                if(a_grid_x<grid_x-1){
                    if(map->get_at(a_grid_x+1, a_grid_y)!=nullptr){
                        if(map->get_at(a_grid_x+1, a_grid_y)->get_type()==Entities::Type::WALL){
                           a_grid_x=a_grid_x;
                        }else{
                            a_grid_x=a_grid_x+1;
                        }
                    }else{
                        a_grid_x=a_grid_x+1;
                    }
                }else{
                    if(map->get_at(0, a_grid_y)!=nullptr){
                        if(map->get_at(0, a_grid_y)->get_type()==Entities::Type::WALL){
                           a_grid_x=a_grid_x;
                        }else{
                            a_grid_x=0;
                        }
                    }else{
                        a_grid_x=0;
                    }
                }
                player_a->set_x(a_grid_x);
            break;
        }
        //Powerup effects for player_a
        if(map->get_at(player_a->get_x(), player_a->get_y())!=nullptr){
            int type=rand()%(5-2+1)+2;
            Entities::Type on_grid=map->get_at(player_a->get_x(), player_a->get_y())->get_type();
            switch(on_grid){
                case Entities::Type::SPEEDUP:
                    player_a->set_speed(1);
                    map->demolish_at(player_a->get_x(), player_a->get_y());
                    map->gen_powerups(type);
                break;
                case Entities::Type::SPEEDDOWN:
                    player_b->set_speed(3);
                    map->demolish_at(player_a->get_x(), player_a->get_y());
                    map->gen_powerups(type);
                break;
                case Entities::Type::SCOREBUFF:
                    //scorebuff function
                    player_a->set_scorebuff();
                    map->demolish_at(player_a->get_x(), player_a->get_y());
                    map->gen_powerups(type);
                break;
                case Entities::Type::ATTACK:
                    player_a->set_can_eat();
                    map->demolish_at(player_a->get_x(), player_a->get_y());
                    map->gen_powerups(type);
                break;
                case Entities::Type::SMALLDOTS:
                    player_a->set_score(1);
                    chomp->play();
                    map->demolish_at(player_a->get_x(), player_a->get_y());
                    smalldot_num=smalldot_num-1;
                break;
                case Entities::Type::BIGDOTS:
                    //Big dots function
                    player_a->set_can_eat_ghost();
                    player_b->set_can_eat_ghost();
                    background_music->stop();
                    background_can_eat_ghost->play();
                    map->demolish_at(player_a->get_x(), player_a->get_y());
                break;
                default:
                break;
            }
        }
    }
    /****** PLAYER EAT PLAYER (AFTER A MOVES) ******/
    player_eat_player_determinaion();
    /****** END OF PLAYER EAT PLAYER (AFTER A MOVES) ******/

    /****** GHOST EATS PLAYER (AFTER A MOVES) ******/
    ghost_eat_player_determination();
    /****** END OF GHOST EATS PLAYER (AFTER A MOVES) ******/

    //Move player b
    if(tick%player_b->get_speed()==0){
        switch(player_b->get_status()){
            case Player::PlayerStatus::UP:
                if(b_grid_y>0){
                    if(map->get_at(b_grid_x, b_grid_y-1)!=nullptr){
                        if(map->get_at(b_grid_x, b_grid_y-1)->get_type()==Entities::Type::WALL){
                            b_grid_y=b_grid_y;
                        }else{
                            b_grid_y=b_grid_y-1;
                        }

                    }else{
                        b_grid_y=b_grid_y-1;
                    }

                }else{
                    if(map->get_at(b_grid_x, grid_y-1)!=nullptr){
                        if(map->get_at(b_grid_x, grid_y-1)->get_type()==Entities::Type::WALL){
                            b_grid_y=b_grid_y;
                        }else{
                            b_grid_y=grid_y-1;
                        }
                    }else{
                        b_grid_y=grid_y-1;
                    }
                }
                player_b->set_y(b_grid_y);
            break;
            case Player::PlayerStatus::DOWN:
                if(b_grid_y<grid_y-1){
                    if(map->get_at(b_grid_x, b_grid_y+1)!=nullptr){
                        if(map->get_at(b_grid_x, b_grid_y+1)->get_type()==Entities::Type::WALL){
                            b_grid_y=b_grid_y;
                        }else{
                            b_grid_y=b_grid_y+1;
                        }

                    }else{
                        b_grid_y=b_grid_y+1;
                    }

                }else{
                    if(map->get_at(b_grid_x, 0)!=nullptr){
                        if(map->get_at(b_grid_x, 0)->get_type()==Entities::Type::WALL){
                            b_grid_y=b_grid_y;
                        }else{
                            b_grid_y=0;
                        }
                    }else{
                        b_grid_y=0;
                    }
                    b_grid_y=0;
                }
                    player_b->set_y(b_grid_y);
            break;
            case Player::PlayerStatus::LEFT:
                if(b_grid_x>0){
                    if(map->get_at(b_grid_x-1, b_grid_y)!=nullptr){
                        if(map->get_at(b_grid_x-1, b_grid_y)->get_type()==Entities::Type::WALL){
                           b_grid_x=b_grid_x;
                        }else{
                            b_grid_x=b_grid_x-1;
                        }
                    }else{
                        b_grid_x=b_grid_x-1;
                    }
                }else{
                    if(map->get_at(grid_x-1, b_grid_y)!=nullptr){
                        if(map->get_at(grid_x-1, b_grid_y)->get_type()==Entities::Type::WALL){
                           b_grid_x=b_grid_x;
                        }else{
                            b_grid_x=grid_x-1;
                        }
                    }else{
                        b_grid_x=grid_x-1;
                    }
                }
                player_b->set_x(b_grid_x);
            break;
            case Player::PlayerStatus::RIGHT:
                if(b_grid_x<grid_x-1){
                    if(map->get_at(b_grid_x+1, b_grid_y)!=nullptr){
                        if(map->get_at(b_grid_x+1, b_grid_y)->get_type()==Entities::Type::WALL){
                           b_grid_x=b_grid_x;
                        }else{
                            b_grid_x=b_grid_x+1;
                        }
                    }else{
                        b_grid_x=b_grid_x+1;
                    }
                }else{
                    if(map->get_at(0, b_grid_y)!=nullptr){
                        if(map->get_at(0, b_grid_y)->get_type()==Entities::Type::WALL){
                           b_grid_x=b_grid_x;
                        }else{
                            b_grid_x=0;
                        }
                    }else{
                        b_grid_x=0;
                    }
                }
                player_b->set_x(b_grid_x);
            break;
        }

        /****** PLAYER EAT PLAYER (AFTER B MOVES) ******/
        player_eat_player_determinaion();
        /****** END OF PLAYER EAT PLAYER (AFTER B MOVES) ******/

        /****** GHOST EATS PLAYER (AFTER B MOVES) ******/
        ghost_eat_player_determination();
        /****** END OF GHOST EATS PLAYER_B (AFTER B MOVES) ******/

        //Powerup effects for player_b
        if(map->get_at(player_b->get_x(), player_b->get_y())!=nullptr){
            int type=rand()%(5-2+1)+2;
            Entities::Type on_grid=map->get_at(player_b->get_x(), player_b->get_y())->get_type();
            switch(on_grid){
                case Entities::Type::SPEEDUP:
                    player_b->set_speed(1);
                    map->demolish_at(player_b->get_x(), player_b->get_y());
                    map->gen_powerups(type);
                break;
                case Entities::Type::SPEEDDOWN:
                    player_a->set_speed(3);
                    map->demolish_at(player_b->get_x(), player_b->get_y());
                    map->gen_powerups(type);
                break;
                case Entities::Type::SCOREBUFF:
                    //scorebuff function
                    player_b->set_scorebuff();
                    map->demolish_at(player_b->get_x(), player_b->get_y());
                    map->gen_powerups(type);
                break;
                case Entities::Type::ATTACK:
                    player_b->set_can_eat();
                    map->demolish_at(player_b->get_x(), player_b->get_y());
                    map->gen_powerups(type);
                break;
                case Entities::Type::SMALLDOTS:
                    player_b->set_score(1);
                    chomp->play();
                    map->demolish_at(player_b->get_x(), player_b->get_y());
                    smalldot_num=smalldot_num-1;

                break;
                case Entities::Type::BIGDOTS:
                    //Big dots function
                    player_b->set_can_eat_ghost();
                    player_a->set_can_eat_ghost();
                    background_music->stop();
                    background_can_eat_ghost->play();
                    map->demolish_at(player_b->get_x(), player_b->get_y());
                break;
                default:
                break;
            }
        }

    }

    // Set period of player a's speed-related powerups
    switch(player_a->get_speed()){
        case 1:
            if(player_a->speed_up_time>=7){
                player_a->set_speed(2);
            }else{
                player_a->speed_up_time=player_a->speed_up_time+1;
            }
        break;
        case 3:
            if(player_a->slow_down_time>=10){
                player_a->set_speed(2);
            }else{
                player_a->slow_down_time=player_a->slow_down_time+1;
            }
        break;
    }
    //Set period of player b's speed-related powerups
    switch(player_b->get_speed()){
        case 1:
            if(player_b->speed_up_time>=7){
                player_b->set_speed(2);
            }else{
                player_b->speed_up_time=player_b->speed_up_time+1;
            }
        break;
        case 3:
            if(player_b->slow_down_time>=10){
                player_b->set_speed(2);
            }else{
                player_b->slow_down_time=player_b->slow_down_time+1;
            }
        break;
    }

    //update player a's powerup time
    player_a->update_all();
    //update player b's powerup time
    player_b->update_all();

    //update the background music
    if(player_a->can_eat_ghost==false && player_b->can_eat_ghost==false){
        background_music->play();
        background_can_eat_ghost->stop();
    }
    if(smalldot_num <= 0){
        background_music->stop();
        background_can_eat_ghost->stop();
    }

    //update animation index
    if(player_animation_reverse == false){
        player_animation++;
    }
    else{
        player_animation--;
    }

    if(player_animation == 5){
        player_animation_reverse = true;
    }
    else if(player_animation == 0){
        player_animation_reverse = false;
    }

    player_switch_color = !player_switch_color;

    /******* GHOST PART *******/

    // Move the ghost out of spawn area
    srand((unsigned)time(0));

    if(tick%ghost_b->get_speed() == 0 && ghost_b->detect_spawn_area() == true) ghost_b->ghost_move_out();
    else if(tick%ghost_b->get_speed() == 0 && ghost_b->detect_spawn_area() == false) ghost_b->ghost_move((rand()));

    if(tick%ghost_o->get_speed() == 0 && ghost_o->detect_spawn_area() == true) ghost_o->ghost_move_out();
    else if(tick%ghost_o->get_speed() == 0 && ghost_o->detect_spawn_area() == false) ghost_o->ghost_move((rand()));

    if(tick%ghost_p->get_speed() == 0 && ghost_p->detect_spawn_area() == true) ghost_p->ghost_move_out();
    else if(tick%ghost_p->get_speed() == 0 && ghost_p->detect_spawn_area() == false) ghost_p->ghost_move((rand()));

    if(tick%ghost_r->get_speed() == 0 && ghost_r->detect_spawn_area() == true) ghost_r->ghost_move_out();
    else if(tick%ghost_r->get_speed() == 0 && ghost_r->detect_spawn_area() == false) ghost_r->ghost_move((rand()));

    // detect player nearby
    ghost_b->detect_player(player_a, player_b,a_grid_x, a_grid_y, b_grid_x, b_grid_y);
    ghost_o->detect_player(player_a, player_b,a_grid_x, a_grid_y, b_grid_x, b_grid_y);
    ghost_p->detect_player(player_a, player_b,a_grid_x, a_grid_y, b_grid_x, b_grid_y);
    ghost_r->detect_player(player_a, player_b,a_grid_x, a_grid_y, b_grid_x, b_grid_y);

    /******* END OF GHOST PART *******/
    repaint(0, 0, width(), height());
    ++tick;
}

void GameWidget::keyPressEvent(QKeyEvent* event) {
    //Detect key presses
    switch (event->key()) {
    case Qt::Key::Key_W:
        if(map->get_at(a_grid_x, a_grid_y-1)!=nullptr){
            if(map->get_at(a_grid_x, a_grid_y-1)->get_type()!=Entities::Type::WALL){
                player_a->set_status(Player::PlayerStatus::UP);
            }
        }else{
            player_a->set_status(Player::PlayerStatus::UP);
        }
        break;
    case Qt::Key::Key_S:
        if(map->get_at(a_grid_x, a_grid_y+1)!=nullptr){
            if(map->get_at(a_grid_x, a_grid_y+1)->get_type()!=Entities::Type::WALL){
                player_a->set_status(Player::PlayerStatus::DOWN);
            }
        }else{
            player_a->set_status(Player::PlayerStatus::DOWN);
        }
        break;
    case Qt::Key::Key_A:
        if(map->get_at(a_grid_x-1, a_grid_y)!=nullptr){
            if(map->get_at(a_grid_x-1, a_grid_y)->get_type()!=Entities::Type::WALL){
                player_a->set_status(Player::PlayerStatus::LEFT);
            }
        }else{
            player_a->set_status(Player::PlayerStatus::LEFT);
        }
        break;
    case Qt::Key::Key_D:
        if(map->get_at(a_grid_x+1, a_grid_y)!=nullptr){
            if(map->get_at(a_grid_x+1, a_grid_y)->get_type()!=Entities::Type::WALL){
                player_a->set_status(Player::PlayerStatus::RIGHT);
            }
        }else{
            player_a->set_status(Player::PlayerStatus::RIGHT);
        }
        break;
    case Qt::Key::Key_Up:
        if(map->get_at(b_grid_x, b_grid_y-1)!=nullptr){
            if(map->get_at(b_grid_x, b_grid_y-1)->get_type()!=Entities::Type::WALL){
                player_b->set_status(Player::PlayerStatus::UP);
            }
        }else{
            player_b->set_status(Player::PlayerStatus::UP);
        }
        break;
    case Qt::Key::Key_Down:
        if(map->get_at(b_grid_x, b_grid_y+1)!=nullptr){
            if(map->get_at(b_grid_x, b_grid_y+1)->get_type()!=Entities::Type::WALL){
                player_b->set_status(Player::PlayerStatus::DOWN);
            }
        }else{
            player_b->set_status(Player::PlayerStatus::DOWN);
        }
        break;
    case Qt::Key::Key_Left:
        if(map->get_at(b_grid_x-1, b_grid_y)!=nullptr){
            if(map->get_at(b_grid_x-1, b_grid_y)->get_type()!=Entities::Type::WALL){
                player_b->set_status(Player::PlayerStatus::LEFT);
            }
        }else{
            player_b->set_status(Player::PlayerStatus::LEFT);
        }
        break;
    case Qt::Key::Key_Right:
        if(map->get_at(b_grid_x+1, b_grid_y)!=nullptr){
            if(map->get_at(b_grid_x+1, b_grid_y)->get_type()!=Entities::Type::WALL){
                player_b->set_status(Player::PlayerStatus::RIGHT);
            }
        }else{
            player_b->set_status(Player::PlayerStatus::RIGHT);
        }
        break;
    }
}



void GameWidget::wheelEvent(QWheelEvent* event) {
    scale = (float) (scale * exp(event->angleDelta().y() / 720.0));
    if (scale > 10.0f) {
        scale = 10.0f;
    }
    if (scale < 0.1f) {
        scale = 0.1f;
    }
}


void GameWidget::obtain_grid_coordinates_from_real(int rx, int ry, int& x, int& y) {
    x = (rx + grid_x * 50) / 100;
    y = (ry + grid_y * 50) / 100;
}

void GameWidget::obtain_grid_coordinates(int dispx, int dispy, int& x, int& y) {
    int rx, ry;
    to_real_coordinates(dispx, dispy, rx, ry);
    obtain_grid_coordinates_from_real(rx, ry, x, y);
}

void GameWidget::to_display_coordinates(int x, int y, int& dispx, int& dispy) {
    float fx = x, fy = y;
    dispx = (int)((fx - scroll_x) * scale) + width() / 2;
    dispy = (int)((fy - scroll_y) * scale) + height() / 2;
}

void GameWidget::to_real_coordinates(int dispx, int dispy, int& x, int& y) {
    float fx = dispx - width() / 2, fy = dispy - height() / 2;

    x = (int)(fx / scale + scroll_x);
    y = (int)(fy / scale + scroll_y);
}

void GameWidget::drawLine(QPainter& paint, int x1, int y1, int x2, int y2) {
    int dispx1, dispx2, dispy1, dispy2;

    to_display_coordinates(x1, y1, dispx1, dispy1);
    to_display_coordinates(x2, y2, dispx2, dispy2);

    paint.drawLine(dispx1, dispy1, dispx2, dispy2);
}

void GameWidget::fillRect(QPainter& paint, int x, int y, int w, int h, const QBrush& brush) {
    int dispx1, dispx2, dispy1, dispy2;

    to_display_coordinates(x, y, dispx1, dispy1);
    to_display_coordinates(x + w, y + h, dispx2, dispy2);

    paint.fillRect(dispx1, dispy1, dispx2 - dispx1, dispy2 - dispy1, brush);
}

void GameWidget::drawPixmap(QPainter& paint, int x, int y, int w, int h, const QPixmap& pixmap) {
    int dispx1, dispx2, dispy1, dispy2;

    to_display_coordinates(x, y, dispx1, dispy1);
    to_display_coordinates(x + w, y + h, dispx2, dispy2);

    paint.drawPixmap(dispx1, dispy1, dispx2 - dispx1, dispy2 - dispy1, pixmap);
}


// Helper function
void tsetColor(QPainter& paint, int dcolor) {
    QPen p = paint.pen();
    p.setWidth(7);
    switch (dcolor) {
    case -1:
        p.setColor(QColor::fromRgb(255, 0, 0));
        break;
    case 0:
        p.setColor(QColor::fromRgb(255, 255, 255));
        break;
    case 1:
        p.setColor(QColor::fromRgb(0, 255, 0));
        break;
    }
    paint.setPen(p);
}

void GameWidget::paintEvent(QPaintEvent* event) {
    QPainter paint{ this };
    // Set black background
    paint.fillRect(0, 0, width(), height(), QBrush{ QColor::fromRgb(0,0,0) });
    QFont ft;
    ft.setPixelSize(25);
    ft.setBold(true);
    ft.setFamily("Comic Sans MS");
    paint.setFont(ft);

    //Render entities on the map
    for (int x = 0; x < grid_x; x++) {
        for (int y = 0; y < grid_y; y++) {

            if (!map->is_empty_at(x, y)) {
                if(map->get_at(x, y)->get_type()==Entities::Type::WALL){

                    fillRect(paint, (x-grid_x/2)*100, (y-grid_y/2)*100, 100, 100, QBrush{QColor::fromRgb(0, 0, 255)});
                }else{
                    drawPixmap(paint, (x - grid_x / 2) * 100, (y - grid_y / 2) * 100, 100, 100,
                               ICONS[static_cast<int>(map->get_at(x, y)->get_type()) - 2]);
                }

            }
        }
    }

    //Render Players
    if (a_grid_x >= 0 && a_grid_y >= 0 && a_grid_x < grid_x && a_grid_y < grid_y){
        QPixmap player_a_icon;
        QPixmap player_b_icon;
        switch(player_a->get_status()){
            case Player::PlayerStatus::UP:
                if(player_b->can_eat==true){
                    if(player_switch_color == true){
                        player_a_icon = PLAYER_SCARED_ICONS[player_animation].transformed(QTransform().rotate(270));
                    }
                    else{
                        player_a_icon = PLAYER_A_ICONS[player_animation].transformed(QTransform().rotate(270));
                    }
                }
                else{
                    player_a_icon = PLAYER_A_ICONS[player_animation].transformed(QTransform().rotate(270));
                }
            break;
            case Player::PlayerStatus::DOWN:
            if(player_b->can_eat==true){
                if(player_switch_color == true){
                    player_a_icon = PLAYER_SCARED_ICONS[player_animation].transformed(QTransform().rotate(90));
                }
                else{
                    player_a_icon = PLAYER_A_ICONS[player_animation].transformed(QTransform().rotate(90));
                }
            }
            else{
                player_a_icon = PLAYER_A_ICONS[player_animation].transformed(QTransform().rotate(90));
            }
            break;
            case Player::PlayerStatus::LEFT:
            if(player_b->can_eat==true){
                if(player_switch_color == true){
                    player_a_icon = PLAYER_SCARED_ICONS[player_animation].transformed(QTransform().rotate(180));
                }
                else{
                    player_a_icon = PLAYER_A_ICONS[player_animation].transformed(QTransform().rotate(180));
                }
            }
            else{
                player_a_icon = PLAYER_A_ICONS[player_animation].transformed(QTransform().rotate(180));
            }
            break;
            case Player::PlayerStatus::RIGHT:
            if(player_b->can_eat==true){
                if(player_switch_color == true){
                    player_a_icon = PLAYER_SCARED_ICONS[player_animation];
                }
                else{
                    player_a_icon = PLAYER_A_ICONS[player_animation];
                }
            }
            else{
                player_a_icon = PLAYER_A_ICONS[player_animation];
            }
            break;
        }
        switch(player_b->get_status()){
            case Player::PlayerStatus::UP:
                if(player_a->can_eat == true){
                    if(player_switch_color == true){
                        player_b_icon = PLAYER_SCARED_ICONS[player_animation].transformed(QTransform().rotate(270));
                    }
                    else{
                        player_b_icon = PLAYER_B_ICONS[player_animation].transformed(QTransform().rotate(270));
                    }
                }
                else{
                player_b_icon = PLAYER_B_ICONS[player_animation].transformed(QTransform().rotate(270));
                }
            break;
            case Player::PlayerStatus::DOWN:
                if(player_a->can_eat == true){
                    if(player_switch_color == true){
                        player_b_icon = PLAYER_SCARED_ICONS[player_animation].transformed(QTransform().rotate(90));
                    }
                    else{
                        player_b_icon = PLAYER_B_ICONS[player_animation].transformed(QTransform().rotate(90));
                    }
                }
                else{
                player_b_icon = PLAYER_B_ICONS[player_animation].transformed(QTransform().rotate(90));
                }
            break;
            case Player::PlayerStatus::LEFT:
                if(player_a->can_eat == true){
                    if(player_switch_color == true){
                        player_b_icon = PLAYER_SCARED_ICONS[player_animation].transformed(QTransform().rotate(180));
                    }
                    else{
                        player_b_icon = PLAYER_B_ICONS[player_animation].transformed(QTransform().rotate(180));
                    }
                }
                else{
                player_b_icon = PLAYER_B_ICONS[player_animation].transformed(QTransform().rotate(180));
                }
            break;
            case Player::PlayerStatus::RIGHT:
                if(player_a->can_eat == true){
                    if(player_switch_color == true){
                        player_b_icon = PLAYER_SCARED_ICONS[player_animation];
                    }
                    else{
                        player_b_icon = PLAYER_B_ICONS[player_animation];
                    }
                }
                else{
                player_b_icon = PLAYER_B_ICONS[player_animation];
                }
            break;
        }

        drawPixmap(paint, (a_grid_x - grid_x / 2) * 100, (a_grid_y - grid_y / 2) * 100, 100,
                   100, player_a_icon);
        drawPixmap(paint, (b_grid_x - grid_x / 2) * 100, (b_grid_y - grid_y / 2) * 100, 100,
                   100, player_b_icon);
    }

    /****** THE GHOST PART ******/

    // render blue ghost
    if (ghost_b->get_x() >= 0 && ghost_b->get_y() >= 0 && ghost_b->get_x() < grid_x && ghost_b->get_y() < grid_y){
        QPixmap ghost_b_icon;
        if(player_a->can_eat_ghost == false && player_b->can_eat_ghost == false){
            switch (ghost_b->get_status()) {
                case Ghost::GhostStatus::UP:
                    ghost_b_icon = GHOSTS_ICONS[0][player_switch_color];
                    break;
                case Ghost::GhostStatus::DOWN:
                    ghost_b_icon = GHOSTS_ICONS[1][player_switch_color];
                    break;
                case Ghost::GhostStatus::LEFT:
                    ghost_b_icon = GHOSTS_ICONS[2][player_switch_color];
                    break;
                case Ghost::GhostStatus::RIGHT:
                    ghost_b_icon = GHOSTS_ICONS[3][player_switch_color];
                    break;
            }
        }
        else{
            if((player_a->can_eat_ghost_time <= 15) || (player_b->can_eat_ghost_time <= 15)){
                ghost_b_icon = GHOSTS_SCARED_ICONS[player_switch_color][player_switch_color];
            }
            else{
                ghost_b_icon = GHOSTS_SCARED_ICONS[0][player_switch_color];
            }
        }

        drawPixmap(paint, (ghost_b->get_x() - grid_x / 2) * 100, (ghost_b->get_y() - grid_y / 2) * 100, 100,
                   100, ghost_b_icon);
    }

    // render orange ghost
    if (ghost_o->get_x() >= 0 && ghost_o->get_y() >= 0 && ghost_o->get_x() < grid_x && ghost_o->get_y() < grid_y){
        QPixmap ghost_o_icon;
        if(player_a->can_eat_ghost == false && player_b->can_eat_ghost == false){
            switch (ghost_o->get_status()) {
                case Ghost::GhostStatus::UP:
                    ghost_o_icon = GHOSTS_ICONS[4][player_switch_color];
                    break;
                case Ghost::GhostStatus::DOWN:
                    ghost_o_icon = GHOSTS_ICONS[5][player_switch_color];
                    break;
                case Ghost::GhostStatus::LEFT:
                    ghost_o_icon = GHOSTS_ICONS[6][player_switch_color];
                    break;
                case Ghost::GhostStatus::RIGHT:
                    ghost_o_icon = GHOSTS_ICONS[7][player_switch_color];
                    break;
            }
        }
        else{
            if((player_a->can_eat_ghost_time <= 15) || (player_b->can_eat_ghost_time <= 15)){
                ghost_o_icon = GHOSTS_SCARED_ICONS[player_switch_color][player_switch_color];
            }
            else{
                ghost_o_icon = GHOSTS_SCARED_ICONS[0][player_switch_color];
            }
        }
        drawPixmap(paint, (ghost_o->get_x() - grid_x / 2) * 100, (ghost_o->get_y() - grid_y / 2) * 100, 100,
                   100, ghost_o_icon);
    }

    // render pink ghost
    if (ghost_p->get_x() >= 0 && ghost_p->get_y() >= 0 && ghost_p->get_x() < grid_x && ghost_p->get_y() < grid_y){
        QPixmap ghost_p_icon;
        if(player_a->can_eat_ghost == false && player_b->can_eat_ghost == false){
            switch (ghost_p->get_status()) {
                case Ghost::GhostStatus::UP:
                    ghost_p_icon = GHOSTS_ICONS[8][player_switch_color];
                    break;
                case Ghost::GhostStatus::DOWN:
                    ghost_p_icon = GHOSTS_ICONS[9][player_switch_color];
                    break;
                case Ghost::GhostStatus::LEFT:
                    ghost_p_icon = GHOSTS_ICONS[10][player_switch_color];
                    break;
                case Ghost::GhostStatus::RIGHT:
                    ghost_p_icon = GHOSTS_ICONS[11][player_switch_color];
                    break;
            }
        }
        else{
            if((player_a->can_eat_ghost_time <= 15) || (player_b->can_eat_ghost_time <= 15)){
                ghost_p_icon = GHOSTS_SCARED_ICONS[player_switch_color][player_switch_color];
            }
            else{
                ghost_p_icon = GHOSTS_SCARED_ICONS[0][player_switch_color];
            }
        }
        drawPixmap(paint, (ghost_p->get_x() - grid_x / 2) * 100, (ghost_p->get_y() - grid_y / 2) * 100, 100,
                   100, ghost_p_icon);
    }

    // render red ghost
    if (ghost_r->get_x() >= 0 && ghost_r->get_y() >= 0 && ghost_r->get_x() < grid_x && ghost_r->get_y() < grid_y){
        QPixmap ghost_r_icon;
        if(player_a->can_eat_ghost == false && player_b->can_eat_ghost == false){
            switch (ghost_r->get_status()) {
                case Ghost::GhostStatus::UP:
                    ghost_r_icon = GHOSTS_ICONS[12][player_switch_color];
                    break;
                case Ghost::GhostStatus::DOWN:
                    ghost_r_icon = GHOSTS_ICONS[13][player_switch_color];
                    break;
                case Ghost::GhostStatus::LEFT:
                    ghost_r_icon = GHOSTS_ICONS[14][player_switch_color];
                    break;
                case Ghost::GhostStatus::RIGHT:
                    ghost_r_icon = GHOSTS_ICONS[15][player_switch_color];
                    break;
            }
        }
        else{
            if((player_a->can_eat_ghost_time <= 15) || (player_b->can_eat_ghost_time <= 15)){
                ghost_r_icon = GHOSTS_SCARED_ICONS[player_switch_color][player_switch_color];
            }
            else{
                ghost_r_icon = GHOSTS_SCARED_ICONS[0][player_switch_color];
            }
        }
        drawPixmap(paint, (ghost_r->get_x() - grid_x / 2) * 100, (ghost_r->get_y() - grid_y / 2) * 100, 100,
                   100, ghost_r_icon);
    }

    /****** THE END OF THE GHOST PART ******/

#define STAT_WIDTH 500
#define HEIGHT 40
    //Draw score
    paint.setPen(Qt::white);
    paint.drawText(450, 10 + HEIGHT, STAT_WIDTH, 50, Qt::AlignTop, "P1:" + QString::number(player_a->get_score()));
    paint.drawText(1025, 10 + HEIGHT, STAT_WIDTH, 50, Qt::AlignTop, "P2:" + QString::number(player_b->get_score()));

}

void GameWidget::load_icons() {
    ICONS = new QPixmap[6]{ {":/images/images/speedup.png"},
                            {":/images/images/speeddown.png"},
                            {":/images/images/scorebuff.png"},
                            {":/images/images/attack.png"},
                            {":/images/images/smalldot.png"},
                            {":/images/images/bigdot.png"}};
    //player a's animation
    PLAYER_A_ICONS = new QPixmap[7];
    PLAYER_A_ICONS[0] = QPixmap{":/images/images/playera/p1init.png"};
    PLAYER_A_ICONS[1] = QPixmap{":/images/images/playera/p1r1.png"};
    PLAYER_A_ICONS[2] = QPixmap{":/images/images/playera/p1r2.png"};
    PLAYER_A_ICONS[3] = QPixmap{":/images/images/playera/p1r3.png"};
    PLAYER_A_ICONS[4] = QPixmap{":/images/images/playera/p1r4.png"};
    PLAYER_A_ICONS[5] = QPixmap{":/images/images/playera/p1r5.png"};

    //player b's animation
    PLAYER_B_ICONS = new QPixmap[7];
    PLAYER_B_ICONS[0] = QPixmap{":/images/images/playerb/p2init.png"};
    PLAYER_B_ICONS[1] = QPixmap{":/images/images/playerb/p2r1.png"};
    PLAYER_B_ICONS[2] = QPixmap{":/images/images/playerb/p2r2.png"};
    PLAYER_B_ICONS[3] = QPixmap{":/images/images/playerb/p2r3.png"};
    PLAYER_B_ICONS[4] = QPixmap{":/images/images/playerb/p2r4.png"};
    PLAYER_B_ICONS[5] = QPixmap{":/images/images/playerb/p2r5.png"};

    // animation for scared player
    PLAYER_SCARED_ICONS = new QPixmap[7];
    PLAYER_SCARED_ICONS[0] = QPixmap{":/images/images/player_scared/spinit.png"};
    PLAYER_SCARED_ICONS[1] = QPixmap{":/images/images/player_scared/spr1.png"};
    PLAYER_SCARED_ICONS[2] = QPixmap{":/images/images/player_scared/spr2.png"};
    PLAYER_SCARED_ICONS[3] = QPixmap{":/images/images/player_scared/spr3.png"};
    PLAYER_SCARED_ICONS[4] = QPixmap{":/images/images/player_scared/spr4.png"};
    PLAYER_SCARED_ICONS[5] = QPixmap{":/images/images/player_scared/spr5.png"};


    GHOSTS_ICONS = new QPixmap*[16];
    for(int i=0; i<16; i++){
        GHOSTS_ICONS[i]= new QPixmap[2];
    }
    GHOSTS_ICONS[0][0]=QPixmap(":/images/images/b_ghostupblue1.png");
    GHOSTS_ICONS[0][1]=QPixmap(":/images/images/b_ghostupblue2.png");
    GHOSTS_ICONS[1][0]=QPixmap(":/images/images/b_ghostdownblue1.png");
    GHOSTS_ICONS[1][1]=QPixmap(":/images/images/b_ghostdownblue2.png");
    GHOSTS_ICONS[2][0]=QPixmap(":/images/images/b_ghostleftblue1.png");
    GHOSTS_ICONS[2][1]=QPixmap(":/images/images/b_ghostleftblue2.png");
    GHOSTS_ICONS[3][0]=QPixmap(":/images/images/b_ghostrightblue1.png");
    GHOSTS_ICONS[3][1]=QPixmap(":/images/images/b_ghostrightblue2.png");

    GHOSTS_ICONS[4][0]=QPixmap(":/images/images/o_ghostuporange1.png");
    GHOSTS_ICONS[4][1]=QPixmap(":/images/images/o_ghostuporange2.png");
    GHOSTS_ICONS[5][0]=QPixmap(":/images/images/o_ghostdownorange1.png");
    GHOSTS_ICONS[5][1]=QPixmap(":/images/images/o_ghostdownorange2.png");
    GHOSTS_ICONS[6][0]=QPixmap(":/images/images/o_ghostleftorange1.png");
    GHOSTS_ICONS[6][1]=QPixmap(":/images/images/o_ghostleftorange1.png");
    GHOSTS_ICONS[7][0]=QPixmap(":/images/images/o_ghostrightorange1.png");
    GHOSTS_ICONS[7][1]=QPixmap(":/images/images/o_ghostrightorange2.png");

    GHOSTS_ICONS[8][0]=QPixmap(":/images/images/p_ghostup1.png");
    GHOSTS_ICONS[8][1]=QPixmap(":/images/images/p_ghostup2.png");
    GHOSTS_ICONS[9][0]=QPixmap(":/images/images/p_ghostdown1.png");
    GHOSTS_ICONS[9][1]=QPixmap(":/images/images/p_ghostdown2.png");
    GHOSTS_ICONS[10][0]=QPixmap(":/images/images/p_ghostleft1.png");
    GHOSTS_ICONS[10][1]=QPixmap(":/images/images/p_ghostleft2.png");
    GHOSTS_ICONS[11][0]=QPixmap(":/images/images/p_ghostright1.png");
    GHOSTS_ICONS[11][1]=QPixmap(":/images/images/p_ghostright2.png");

    GHOSTS_ICONS[12][0]=QPixmap(":/images/images/r_ghostupred1.png");
    GHOSTS_ICONS[12][1]=QPixmap(":/images/images/r_ghostupred2.png");
    GHOSTS_ICONS[13][0]=QPixmap(":/images/images/r_ghostdownred1.png");
    GHOSTS_ICONS[13][1]=QPixmap(":/images/images/r_ghostdownred2.png");
    GHOSTS_ICONS[14][0]=QPixmap(":/images/images/r_ghostleftred1.png");
    GHOSTS_ICONS[14][1]=QPixmap(":/images/images/r_ghostleftred2.png");
    GHOSTS_ICONS[15][0]=QPixmap(":/images/images/r_ghostrightred1.png");
    GHOSTS_ICONS[15][1]=QPixmap(":/images/images/r_ghostrightred2.png");

    GHOSTS_SCARED_ICONS = new QPixmap*[2];
    for(int i=0; i<2; i++){
        GHOSTS_SCARED_ICONS[i]=new QPixmap[2];
    }
    GHOSTS_SCARED_ICONS[0][0]=QPixmap(":/images/images/ghostscaredblue1.png");
    GHOSTS_SCARED_ICONS[0][1]=QPixmap(":/images/images/ghostscaredblue2.png");
    GHOSTS_SCARED_ICONS[1][0]=QPixmap(":/images/images/ghostscaredwhite1.png");
    GHOSTS_SCARED_ICONS[1][1]=QPixmap(":/images/images/ghostscaredwhite2.png");
}

void GameWidget::dealloc_icons() {
    delete[] ICONS;
    for(int i=0; i<16; i++){
        delete[] GHOSTS_ICONS[i];
    }
    delete[] GHOSTS_ICONS;
}

int GameWidget::return_winner(){
    if(player_a->get_score()>player_b->get_score()){
        return 1;
    }else{
        if(player_a->get_score()<player_b->get_score()){
            return 2;
        }else{
            return 0;
        }
    }
}

/****** THE GHOST PART *******/

int GameWidget::random_x(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(10,15);
    int random_num = dis(gen);
    return random_num;
}

int GameWidget::random_y(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(12,14);
    int random_num = dis(gen);
    return random_num;
}

Ghost::GhostStatus GameWidget::random_direction(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(1,4);
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

void GameWidget::reset_player_a(){
    a_grid_x = 0;
    a_grid_y = 28;
    player_a->set_x(0);
    player_a->set_x(28);
    player_a->set_status(Player::PlayerStatus::UP);
    player_die->play();
}

void GameWidget::reset_player_b(){
    b_grid_x = 25;
    b_grid_y = 28;
    player_b->set_x(25);
    player_b->set_y(28);
    player_a->set_status(Player::PlayerStatus::UP);
    player_die->play();
}

/****** THE END OF THE GHOST PART *******/

void GameWidget::player_eat_player_determinaion(){
    if((a_grid_x == b_grid_x)&&(a_grid_y==b_grid_y)){
        if(player_a->can_eat==true && player_b->can_eat==false){
            player_b->set_score(-10);
            reset_player_b();
        }
        else if(player_a->can_eat==false && player_b->can_eat==true){
            player_a->set_score(-10);
            reset_player_a();
        }
    }
}

// detect if ghost meets player; refer to ghost.cpp for the description of met_player function
void GameWidget::ghost_eat_player_determination(){
    int case_b =ghost_b->met_player(a_grid_x, a_grid_y, b_grid_x, b_grid_y);
    int case_o =ghost_o->met_player(a_grid_x, a_grid_y, b_grid_x, b_grid_y);
    int case_p =ghost_p->met_player(a_grid_x, a_grid_y, b_grid_x, b_grid_y);
    int case_r =ghost_r->met_player(a_grid_x, a_grid_y, b_grid_x, b_grid_y);

    switch (case_b) {
        case 1:
            player_a->set_score(5);
            ghost_b->set_x(random_x());
            ghost_b->set_y(random_y());
            ghost_die->play();
        break;
        case 2:
            player_a->set_score(-10);
            reset_player_a();
        break;
        case 3:
            player_b->set_score(5);
            ghost_b->set_x(random_x());
            ghost_b->set_y(random_y());
            ghost_die->play();
        break;
        case 4:
            player_b->set_score(-10);
            reset_player_b();

    }

    switch (case_o) {
        case 1:
            player_a->set_score(5);
            ghost_o->set_x(random_x());
            ghost_o->set_y(random_y());
            ghost_die->play();
        break;
        case 2:
            player_a->set_score(-10);
            reset_player_a();
        break;
        case 3:
            player_b->set_score(5);
            ghost_o->set_x(random_x());
            ghost_o->set_y(random_y());
            ghost_die->play();
        break;
        case 4:
            player_b->set_score(-10);
            reset_player_b();
    }

    switch (case_p) {
        case 1:
            player_a->set_score(5);
            ghost_p->set_x(random_x());
            ghost_p->set_y(random_y());
            ghost_die->play();
        break;
        case 2:
            player_a->set_score(-10);
            reset_player_a();
        break;
        case 3:
            player_b->set_score(5);
            ghost_p->set_x(random_x());
            ghost_p->set_y(random_y());
            ghost_die->play();
        break;
        case 4:
            player_b->set_score(-10);
            reset_player_b();
    }

    switch (case_r) {
        case 1:
            player_a->set_score(5);
            ghost_r->set_x(random_x());
            ghost_r->set_y(random_y());
            ghost_die->play();
        break;
        case 2:
            player_a->set_score(-10);
            reset_player_a();
        break;
        case 3:
            player_b->set_score(5);
            ghost_r->set_x(random_x());
            ghost_r->set_y(random_y());
            ghost_die->play();
        break;
        case 4:
            player_b->set_score(-10);
            reset_player_b();
    }
}
