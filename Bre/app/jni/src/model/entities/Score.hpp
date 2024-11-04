//
// Created by Jonathan on 31/10/2024.
//

#ifndef BRE_SCORE_HPP
#define BRE_SCORE_HPP

#include "../../controller/components/Rectangle.hpp"

class Score {
    Rectangle rect; //position and size
    int score;
    int highScore;

public:
    Score() : rect(Rectangle(0, 0, 0, 0)), score(0), highScore(0) {}
    Score(Rectangle rect, int highScore) : rect(rect), score(0), highScore(highScore) {}

    void setRect(int x, int y, int w, int h) {
        rect.x = x;
        rect.y = y;
        rect.w = w;
        rect.h = h;
    }

    void setScore(int score) {
        this->score = score;
        if(score > highScore)
            highScore = score;
    }

    void incrementScore() {
        score++;
        if(score > highScore)
            highScore = score;
    }

    int getScore() const {
        return score;
    }

    int getHighScore() const {
        return highScore;
    }

    Rectangle getRect() const {
        return rect;
    }

    void resetForGameOver() {
        score = 0;
    }
};

#endif //BRE_SCORE_HPP
