#ifndef SHIP_H
#define SHIP_H

#include <string>
#include <vector>
#include "rsdl.hpp"
#include "shot.h"

using namespace std;

const int RIGHT = 20;
const int LEFT = -20;
const int UP = -20;
const int DOWN = 20;
const int ATTACK = 1;
const int NOT_ATTACK = 0;
const int SHOT_SPEED = -20;
const char UP_KEY = 'w';
const char DOWN_KEY = 's';
const char RIGHT_KEY = 'd';
const char LEFT_KEY = 'a';
const char ATTACK_KEY = ' ';
const string SHIP_IMAGE = "ship.png";


class Round;

class Ship {
public:
    Ship (Rectangle input_body);
    void handle_key_pressed (char key);
    void handle_key_released (char key);
    void update ();
    void draw ();
    void set_window (Window* input_window);
    bool is_attacked (Shot* shot);
    vector<Shot> get_shots ();
    bool have_meet (Rectangle object);
    
private:
    void attack ();
    bool check_y_location ();
    bool check_x_location ();
    void check_shots_location ();
    bool is_point_in_ship (int x, int y);

    int vx;
    int vy;
    int attack_status;
    Rectangle body;
    Window* window;
    vector<Shot> shots;
};

#endif