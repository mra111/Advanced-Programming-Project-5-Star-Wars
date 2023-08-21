#ifndef SHOT_H
#define SHOT_H

#include "rsdl.hpp"

using namespace std;

const int RADIUS = 5;
const int SHIP_SHOT = 1;
const int ENEMY_SHOT = 2;

class Ship;

class Shot {
public:
    Shot (int input_x, int input_y, int input_speed, int input_type, Window* input_window);
    void update ();
    void draw ();
    bool is_in_window ();
    int get_x ();
    int get_y ();

private:
    int x;
    int y;
    int radius;
    int speed;
    int type;
    Window* window;
};

#endif