//
// Created by jonat on 25/09/2024.
//

#ifndef BRE_GAME_CONTROLLER_HPP
#define BRE_GAME_CONTROLLER_HPP

#include <vector>

using namespace std;

class GameController {

    bool developer_mode = false;

    //TTF_Font *fontFPS;
    //stringstream ssFPS;

    //vector<percorso> prc;
    //vector<CLONE> clone;

    int velocita = 3;
    unsigned short int pw;
    unsigned short int ph;

public:
    GameController() {

    }

    static void init();

    static void render();

    static void update();

    static void handleEvents();

    static void clean();
};

#endif //BRE_GAME_CONTROLLER_HPP