#ifndef ROUND_H
#define ROUND_H

#include <vector>
#include <string>
#include "ship.h"
#include "hostage.h"
#include "enemy1.h"
#include "enemy2.h"

using namespace std;

const int QUIT_GAME = 2;
const int WIN = 1;
const int LOSE = 0;
const int ENEMY1 = 1;
const int ENEMY2 = 2;
const int EXIST = 1;
const int NOT_EXIST = 0;
const int PARAMETR = 200;
const int OBJECT_SIZE = 50;
const string BACKGROUND_IMAGE = "background.png";
const string ENEMY1_CHAR = "E";
const string ENEMY2_CHAR = "M";
const string HOSTAGE_CHAR = "S";


class Round {
public:
    Round (int input_rows_count, int input_column_count, vector<vector<string>> map, string level, 
           Window* input_window);
    void run ();
    int get_result ();

private:
    void proccess ();
    void update ();
    void draw_screen ();
    void set_enemy1 (Enemy1 enemy1);
    void set_enemy2 (Enemy2 enemy2);
    void set_hostage (Hostage hostage);
    void draw_enemies ();
    void draw_hostages ();
    void check_enemies ();
    void check_ship ();
    void check_hostages ();
    void set_map (vector<vector<string>> map);
    void have_acident ();
    
    Window* window;
    Ship ship;
    vector<Enemy1> enemies1;
    vector<Enemy2> enemies2;
    vector<Hostage> hostages;
    string level;
    int round_status;
    int rows_count;
    int columns_count;
    int result;
    int enemies_count;
};

#endif