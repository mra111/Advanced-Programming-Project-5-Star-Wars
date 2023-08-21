#ifndef ENEMY2_H
#define ENEMY2_H

#include "rsdl.hpp"
#include "enemy1.h"

using namespace std;

const int ESAY_ENEMY_SPEED = 5;
const int MEDIUM_ENEMY_SPEED = 10;
const int HARD_ENEMY_SPEED = 15;
const string ENEMY2_IMAGE  = "enemy2.png";


class Enemy2 : public Enemy1 {
public:
    Enemy2 (Rectangle input_body, string level, Window* input_window);
    void update ();
    void draw ();
    
private:
    bool check_location ();
    void move ();
    void set_speed (string level);

    int vx;
};

#endif