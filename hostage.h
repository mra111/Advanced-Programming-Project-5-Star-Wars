#ifndef HOSTAGE_H
#define HOSTAGE_H

#include <string>
#include "rsdl.hpp"
#include "shot.h"

using namespace std;

const string HOSTAGE_IMAGE = "hostage.png";


class Round;

class Hostage {
public:
    Hostage (Rectangle input_body, Window* input_window);
    void draw ();
    bool is_attacked (Shot* shot);
    Rectangle get_body ();
    
private:
    bool is_point_in_hostage (int x, int y);

    Rectangle body;
    Window *window; 
};

#endif