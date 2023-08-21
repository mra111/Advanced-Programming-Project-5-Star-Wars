#include "rsdl.hpp"
#include "game.h"

using namespace std;


Game::Game () {

}

void Game::get_input () {
    fstream map_file (MAP_FILE);
    int num;
    int i;
    int j;
    int k;
    string line;
    string word;
    vector<string> row;
    vector<vector<string>> columns;

    getline (map_file, line);
    word = line[0];
    rows_count = stoi (word);
    word = line[2];
    columns_count = stoi (word);

    getline (map_file, line);
    rounds_count = stoi (line);

    for (i = 0; i < rounds_count; i++) {
        for (j = 0; j < rows_count; j++) {
            getline (map_file, line);
            for (k = 0; k < line.size (); k++) {
                word = line[k];
                row.push_back (word);
            }
            columns.push_back (row);
            row.clear ();
        }

        getline (map_file, line);
        levels.push_back (line);

        if (i != rounds_count - 1) {
            getline (map_file, line);
        }

        maps.push_back (columns);
        columns.clear ();
    }

    map_file.close ();
}

void Game::play_game () {
    int i;
    Window window (PARAMETR * columns_count,  PARAMETR * rows_count, TITLE);

    for (i = 0; i < rounds_count; i++) {
        Round round (rows_count, columns_count, maps[i], levels[i], &window);
        round.run ();
        result = round.get_result ();

        if (result == LOSE || result == QUIT_GAME) {
            break;
        }
    }
}

void Game::print_result () {
    if (result == WIN) {
        cout << "you win" << endl;
    }

    else if (result == LOSE) {
        cout << "you lose" << endl;
    }
}

void Game::run () {
    get_input ();

    play_game ();

    print_result ();
}