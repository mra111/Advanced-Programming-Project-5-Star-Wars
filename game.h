#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "round.h"

using namespace std;

const string MAP_FILE = "map.txt";
const string TITLE = "game";


class Game {
public:
    Game ();
    void run ();

private:
    void get_input ();
    void play_game ();
    void print_result ();

    int rows_count;
    int columns_count;
    int rounds_count;
    int result;
    vector<vector<vector<string>>> maps;
    vector<string> levels;
};

#endif