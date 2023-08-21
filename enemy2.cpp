#include "enemy2.h"

using namespace std;


Enemy2::Enemy2 (Rectangle input_body, string level, Window* input_window) 
               : Enemy1 (input_body, level, input_window) {
    window = input_window;
    wait_time = 0;
    live = ALIVE;
    set_shot_speed (level);
    set_speed (level);
}

bool Enemy2::check_location () {
    if (body.x + vx < 0 || body.x  + body.w + vx > window->get_width ()) {
        return false;
    }
    return true;
}

void Enemy2::move () {
    if (check_location () == false) {
        vx = -vx;
    }
    
    body.x = body.x + vx;
}

void Enemy2::update () {
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

    move ();
}

void Enemy2::draw () {
    int i;
    
    if (live == ALIVE) {
        window->draw_img (ENEMY2_IMAGE, body);
    }

    for (i = 0; i < shots.size (); i++) {
        shots[i].draw ();
    }
}

void Enemy2::set_speed (string level) {
    if (level == "Esay") {
        vx = ESAY_ENEMY_SPEED;
    }
    else if (level == "Medium") {
        vx = MEDIUM_ENEMY_SPEED;
    }
    else if (level == "Hard") {
        vx = HARD_ENEMY_SPEED;
    }
}