#ifndef BRE_PLAYER_HPP
#define BRE_PLAYER_HPP

class Player {
protected:
    int x;
    int y;
    int w;
    int h;
    int screen_w;
    int screen_h;
    const static int speed = 3;
};

#endif //BRE_PLAYER_HPP