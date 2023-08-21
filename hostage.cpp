#include "hostage.h"

using namespace std;


Hostage::Hostage (Rectangle input_body, Window* input_window) : body (input_body) {
    window = input_window;
}

void Hostage::draw () {
    window->draw_img (HOSTAGE_IMAGE, body);
}

bool Hostage::is_point_in_hostage (int x, int y) {
    if (x >= body.x && x <= body.x + body.w && y >= body.y && y <= body.y + body.h) {
        return true;
    }

    return false;
}

bool Hostage::is_attacked (Shot* shot) {
    if (is_point_in_hostage (shot->get_x (), shot->get_y ()) == true) {
        return true;
    }

    return false;
}

Rectangle Hostage::get_body () {
    return body;
}