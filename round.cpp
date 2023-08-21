#include "round.h"
#include "rsdl.hpp"

using namespace std;


Round::Round (int input_rows_count, int input_columns_count, vector<vector<string>> map, string input_level, 
              Window* input_window) : ship (Rectangle ((PARAMETR * input_columns_count) / 2 - (OBJECT_SIZE / 2), 
              PARAMETR * input_rows_count - 100, OBJECT_SIZE, OBJECT_SIZE)) {
    rows_count = input_rows_count;
    columns_count = input_columns_count;
    window = input_window;
    level = input_level;
    ship.set_window (window);
    set_map (map);
    enemies_count = enemies1.size () + enemies2.size ();
}

void Round::check_enemies () {
    int i;
    int j;
    vector<Shot> ship_shots = ship.get_shots ();

    for (i = 0; i < enemies1.size (); i++) {
        for (j = 0; j < ship_shots.size (); j++) {
            if (enemies1[i].is_attacked (&ship_shots[j]) == true && enemies1[i].is_alive () == true) {
                enemies1[i].die ();
                enemies_count = enemies_count - 1;
            }
        }
    }

    for (i = 0; i < enemies2.size (); i++) {
        for (j = 0; j < ship_shots.size (); j++) {
            if (enemies2[i].is_attacked (&ship_shots[j]) == true && enemies2[i].is_alive () == true) {
                enemies2[i].die ();
                enemies_count = enemies_count - 1;
            }
        }
    }

    if (enemies_count == 0) {
        round_status = false;
        result = WIN;
    }
}

void Round::check_ship () {
    int i;
    int j;
    vector<Shot> enemy_shots;

    for (i = 0; i < enemies1.size (); i++) {
        enemy_shots = enemies1[i].get_shots ();
        for (j = 0; j < enemy_shots.size (); j++) {
            if (ship.is_attacked (&enemy_shots[j]) == true) {
                round_status = false;
                result = LOSE;
                break;
            }
        }

        if (result == LOSE) {
            break;
        }
    }

    for (i = 0; i < enemies2.size (); i++) {
        enemy_shots = enemies2[i].get_shots ();
        for (j = 0; j < enemy_shots.size (); j++) {
            if (ship.is_attacked (&enemy_shots[j]) == true) {
                round_status = false;
                result = LOSE;
                break;
            }
        }

        if (result == LOSE) {
            break;
        }
    }
}

void Round::check_hostages () {
    int i;
    int j;
    vector<Shot> ship_shots = ship.get_shots ();

    for (i = 0; i < hostages.size (); i++) {
        for (j = 0; j < ship_shots.size (); j++) {
            if (hostages[i].is_attacked (&ship_shots[j]) == true) {
                round_status = false;
                result = LOSE;
                break;
            }
        }

        if (ship.have_meet (hostages[i].get_body ()) == true) {
            round_status = false;
            result = LOSE;
            break;
        }

        if (result == LOSE) {
            break;
        }
    }
}

void Round::have_acident () {
    int i;

    for (i = 0; i < enemies1.size (); i++) {
        if (enemies1[i].is_alive () == true) {
            if (ship.have_meet (enemies1[i].get_body ()) == true) {
                round_status = false;
                result = LOSE;
                break;
            }
        }
    }

    for (i = 0; i < enemies2.size (); i++) {
        if (enemies2[i].is_alive () == true) {
            if (ship.have_meet (enemies2[i].get_body ()) == true) {
                round_status = false;
                result = LOSE;
                break;
            }
        }
    }
}

void Round::run () {
    round_status = true;

    while (round_status) {
        proccess ();
        update ();
        draw_screen ();
        delay (100);
    }
}

void Round::proccess () {
    while (window->has_pending_event () == true) {
        Event event = window->poll_for_event ();
        if (event.get_type () == Event::KEY_PRESS) {
            ship.handle_key_pressed (event.get_pressed_key ());
        }

        else if (event.get_type () == Event::KEY_RELEASE) {
            ship.handle_key_released (event.get_pressed_key ());
        }

        else if (event.get_type () == Event::QUIT) {
            round_status = false;
            result = QUIT_GAME;
        }
    }
}

void Round::update () {
    int i;

    ship.update ();
    check_enemies ();
    check_ship ();
    check_hostages ();
    have_acident ();

    for (i = 0; i < enemies2.size (); i++) {
        enemies2[i].update ();
    }

    for (i = 0; i < enemies1.size (); i++) {
        enemies1[i].update ();
    }
}

void Round::draw_enemies () {
    int i;

    for (i = 0; i < enemies1.size (); i++) {
        enemies1[i].draw ();
    }

    for (i = 0; i < enemies2.size (); i++) {
        enemies2[i].draw ();
    }

}

void Round::draw_hostages () {
    int i;

    for (i = 0; i < hostages.size (); i++) {
        hostages[i].draw ();
    }
}

void Round::draw_screen () {
    window->clear ();
    window->draw_img (BACKGROUND_IMAGE);
    ship.draw ();
    draw_enemies ();
    draw_hostages ();
    window->update_screen ();
}

void Round::set_enemy1 (Enemy1 enemy1) {
    enemies1.push_back (enemy1);
}

void Round::set_enemy2 (Enemy2 enemy2) {
    enemies2.push_back (enemy2);
}

void Round::set_hostage (Hostage hostage) {
    hostages.push_back (hostage);
}

void Round::set_map (vector<vector<string>> map) {
    int i;
    int j;

    for (i = 0; i < map.size (); i++) {
        for (j = 0; j < map[i].size (); j++) {
            if (map[i][j] == ENEMY1_CHAR) {
                set_enemy1 (Enemy1 (Rectangle (PARAMETR * j + OBJECT_SIZE, PARAMETR * i + OBJECT_SIZE, 
                                               OBJECT_SIZE, OBJECT_SIZE), level, window));
            }

            else if (map[i][j] == ENEMY2_CHAR) {
                set_enemy2 (Enemy2 (Rectangle (PARAMETR * j + OBJECT_SIZE, PARAMETR * i + OBJECT_SIZE, 
                                               OBJECT_SIZE, OBJECT_SIZE), level, window));
            }

            else if (map[i][j] == HOSTAGE_CHAR) {
                set_hostage (Hostage (Rectangle (PARAMETR * j + OBJECT_SIZE, PARAMETR * i + OBJECT_SIZE, 
                                                 OBJECT_SIZE, OBJECT_SIZE), window));
            }
        }
    }
}

int Round::get_result () {
    return result;
}