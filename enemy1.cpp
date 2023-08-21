#include "enemy1.h"

using namespace std;


Enemy1::Enemy1 (Rectangle input_body, string level, Window* input_window) : body (input_body) {
    window = input_window;
    wait_time = 0;
    live = ALIVE;
    set_shot_speed (level);
}

vector<Shot> Enemy1::get_shots () {
    return shots;
}

bool Enemy1::is_attacked (Shot* shot) {
    if (shot->get_x () >= body.x && shot->get_x () <= body.x + body.w && shot->get_y () >= body.y && 
        shot->get_y () <= body.y + body.h) {
        return true;
    }
    return false;
}

void Enemy1::draw () {
    int i;
    
    if (live == ALIVE) {
        window->draw_img (ENEMY1_IMAGE, body);
    }

    for (i = 0; i < shots.size (); i++) {
        shots[i].draw ();
    }
}

void Enemy1::attack () {
    shots.push_back (Shot (body.x + (body.w / 2), body.y, shot_speed, ENEMY_SHOT, window));
}

void Enemy1::check_shots_location () {
    int i;
    
    if (shots.size () > 0) {
        for (i = shots.size () - 1; i >= 0; i--) {
            if (shots[i].is_in_window () == false) {
                shots.erase (shots.begin () + i);
            }
        }
    }
}

void Enemy1::update () {
    int i;
    if (live == ALIVE) {
        if (wait_time == 0) {
            attack ();
            wait_time = wait_time + 1;
        }
        else if (wait_time == shot_wait_time) {
            wait_time = 0;
        }
        else {
            wait_time = wait_time + 1;
        }
    }

    check_shots_location ();

    for (i = 0; i < shots.size (); i++) {
        shots[i].update ();
    }
}

void Enemy1::die () {
    live = DEAD;
}

bool Enemy1::is_alive () {
    if (live == ALIVE) {
        return true;
    }
    return false;
}

Rectangle Enemy1::get_body () {
    return body;
}

void Enemy1::set_shot_speed (string level) {
    if (level == "Esay") {
        shot_speed = ESAY_SHOT_SPEED;
        shot_wait_time = ESAY_SHOT_WAIT_TIME;
    }
    else if (level == "Medium") {
        shot_speed = MEDIUM_SHOT_SPEED;
        shot_wait_time = MEDIUM_SHOT_WAIT_TIME;
    }
    else if (level == "Hard") {
        shot_speed = HARD_SHOT_SPEED;
        shot_wait_time = HARD_SHOT_WAIT_TIME;
    }
}