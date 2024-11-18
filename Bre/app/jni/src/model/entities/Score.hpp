//
// Created by Jonathan on 31/10/2024.
//

#ifndef BRE_SCORE_HPP
#define BRE_SCORE_HPP

#include "../../model/worlds/World.hpp"
#include "../../controller/components/Text.hpp"

class Score : public Text {
    int score = 0;
    int highScore = 0;

public:
    Score() = default;
    Score(int highScore) : Text(
                World::getScreenW()/2,
                World::getScreenH() - dimens::vertical_margin,
                new char[10],
                dimens::huge_title_font_size
            ), score(0), highScore(highScore) {
        sprintf(text, "%d", score);
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

    int getValue() const {
        return score;
    }

    const char* getText() {
        if(text != nullptr)
            sprintf(text, "%d", score);
        return text;
    }

    int getHighScore() const {
        return highScore;
    }

    void resetForGameOver() {
        score = 0;
    }

    ~Score() {
        delete[] text;
    }
};

#endif //BRE_SCORE_HPP
