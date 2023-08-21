#ifndef ENEMY1_H
#define ENEMY1_H

#include <vector>
#include <string>
#include "rsdl.hpp"
#include "shot.h"

using namespace std;

const int ALIVE  = 1;
const int DEAD = 0;
const int ESAY_SHOT_SPEED = 10;
const int ESAY_SHOT_WAIT_TIME = 20;
const int MEDIUM_SHOT_SPEED = 20;
const int MEDIUM_SHOT_WAIT_TIME = 15;
const int HARD_SHOT_SPEED = 25;
const int HARD_SHOT_WAIT_TIME = 10;
const string ENEMY1_IMAGE  = "enemy1.png";


class Round;

class Enemy1 {
public:
    Enemy1 (Rectangle input_body, string level, Window* input_window);
    virtual void draw ();
    virtual void update ();
    bool is_attacked (Shot* shot);
    vector<Shot> get_shots ();
    void die ();
    bool is_alive ();
    Rectangle get_body ();

protected:
    void attack ();
    void check_shots_location ();
    void set_shot_speed (string level);

    int wait_time;
    int live;
    int shot_speed;
    int shot_wait_time;
    Rectangle body;
    Window* window;
    vector<Shot> shots;
};

#endif