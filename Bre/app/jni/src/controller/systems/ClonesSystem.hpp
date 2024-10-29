//
// Created by Jonathan on 23/10/2024.
//

#ifndef BRE_CLONESSYSTEM_HPP
#define BRE_CLONESSYSTEM_HPP

#include <vector>
#include <map>
#include <climits>

#include "../../model/entities/Player.hpp"
#include "../../model/entities/Clone.hpp"
#include "../../controller/components/Point2D.hpp"

class ClonesSystem {

private:
    std::vector<Point2D> path;
    bool isCloneAddable = true;
    bool isMaxNumberOfClonesReached = false;
    int nextCloneKey = 1;
    int framesBetweenEveryClone = 500;
    constexpr const static short int seconds_between_every_clone = 2;

public:
    void updatePlayerPath(const Player* player, const Game* game) {
        if(game->getState() == GameState::PLAYING) {
            path.push_back(Point2D(static_cast<unsigned short>(player->getRect().x),
                                    static_cast<unsigned short>(player->getRect().y)));
            if (path.size() > INT_MAX - 1) {
                path.erase(path.begin(), path.begin() + framesBetweenEveryClone);
                isMaxNumberOfClonesReached = true;
            }
        }
    }

    void addCloneEveryTwoSeconds(std::map<int, Clone>* clones, const Game* game, const Rectangle* screenSize) {
        short int time_in_seconds = game->getTimer().now()/1000;

        if(time_in_seconds!=0) {
            //add clone every 2 seconds
            if (time_in_seconds % seconds_between_every_clone == 0 && isCloneAddable) {
                SDL_Log("time_in_seconds: %d", time_in_seconds);
                if (nextCloneKey == 1) {
                    framesBetweenEveryClone = path.size();
                }
                clones->insert(std::pair<int, Clone>(nextCloneKey++,
                                                        Clone(screenSize->w, screenSize->h)));
                isCloneAddable = false;
            } else if (time_in_seconds % seconds_between_every_clone == 1 && !isMaxNumberOfClonesReached) {
                isCloneAddable = true;
            }
        }
    }

    void moveAllClones(std::map<int, Clone>* clones) {
        //move all clones
        for(auto& clone_pair : *clones) {
            SDL_Log("clone_key: %d", clone_pair.first);
            const int clone_key = clone_pair.first;
            Clone& clone = clone_pair.second;

            if(!path.empty() && path.size() >= clone_key * framesBetweenEveryClone) {
                float x = path[path.size() - clone_key * framesBetweenEveryClone].x;
                float y = path[path.size() - clone_key * framesBetweenEveryClone].y;
                clone.setPosition(x, y);
            }
        }
    }
};

#endif //BRE_CLONESSYSTEM_HPP
