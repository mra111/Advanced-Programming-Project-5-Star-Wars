#include "ship.h"


using namespace std;


Ship::Ship (Rectangle input_body) : body (input_body) {
    vx = 0;
    vy = 0;
    attack_status = NOT_ATTACK;
}

void Ship::handle_key_pressed (char key) {
    if (key == UP_KEY) {
        vy = UP;
    }

    else if (key == DOWN_KEY) {
        vy = DOWN;
    }

    else if (key == RIGHT_KEY) {
        vx = RIGHT;
    }

    else if (key == LEFT_KEY) {
        vx = LEFT;
    }

    else if (key == ATTACK_KEY) {
        attack_status = ATTACK;
    }
}

void Ship::handle_key_released (char key) {
    if (key == UP_KEY || key == DOWN_KEY) {
        vy = 0;
    }

    else if (key == RIGHT_KEY || key == LEFT_KEY) {
        vx = 0;
    }

    else if (key == ATTACK_KEY) {
        attack_status = NOT_ATTACK;
    }
}

void Ship::draw () {
    int i;

    window->draw_img (SHIP_IMAGE, body);

    for (i = 0; i < shots.size (); i++) {
        shots[i].draw ();
    }
}

bool Ship::check_y_location () {
    if (body.y + vy < 0 || body.y + body.h + vy > window->get_height ()) {
        return false;
    }
    return true;
}

bool Ship::check_x_location () {
    if (body.x + vx < 0 || body.x + body.w + vx > window->get_width ()) {
        return false;
    }
    return true;
}

void Ship::attack () {
    shots.push_back (Shot (body.x + (body.w / 2), body.y, SHOT_SPEED, SHIP_SHOT, window));
}

void Ship::set_window (Window* input_window) {
    window = input_window;
}

void Ship::check_shots_location () {
    int i;
    
    if (shots.size () > 0) {
        for (i = shots.size () - 1; i >= 0; i--) {
            if (shots[i].is_in_window () == false) {
                shots.erase (shots.begin () + i);
            }
        }
    }
}

void Ship::update () {
    int i;

    if (check_x_location () == true) {
        body.x = body.x + vx;
    }

    if (check_y_location () == true) {
        body.y = body.y + vy;
    }

    if (attack_status == ATTACK) {
        attack ();
    }

    check_shots_location ();

    for (i = 0; i < shots.size (); i++) {
        shots[i].update ();
    }
}

vector<Shot> Ship::get_shots () {
    return shots;
}

bool Ship::is_point_in_ship (int x, int y) {
    if (x >= body.x && x <= body.x + body.w && y >= body.y && y <= body.y + body.h) {
        return true;
    }

    return false;
}

bool Ship::is_attacked (Shot* shot) {
    if (is_point_in_ship (shot->get_x (), shot->get_y ()) == true) {
        return true;
    }

    return false;
}

bool Ship::have_meet (Rectangle object) {
    if (is_point_in_ship (object.x, object.y) == true || 
    is_point_in_ship (object.x + object.w, object.y) == true || 
    is_point_in_ship (object.x, object.y + object.h) == true || 
    is_point_in_ship (object.x + object.w, object.y + object.h) == true) {
        return true;
    }

    return false;
}