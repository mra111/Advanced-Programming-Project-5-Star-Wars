#include "shot.h"
#include "ship.h"

using namespace std;

Shot::Shot (int input_x, int input_y, int input_speed, int input_type, Window* input_window) {
    x = input_x;
    y = input_y;
    window = input_window;
    speed = input_speed;
    type = input_type;
    radius = RADIUS;
}

void Shot::update () {
    y = y + speed;
}

void Shot::draw () {
    if (type == SHIP_SHOT) {
        window->fill_circle (Point (x, y), radius, WHITE);
    }
    else if (type == ENEMY_SHOT) {
        window->fill_circle (Point (x, y), radius, RED);
    }
}

bool Shot::is_in_window () {
    if (y < 0 || y > window->get_height ()) {
        return false;
    }
    return true;
}

int Shot::get_x () {
    return x;
}

int Shot::get_y () {
    return y;
}