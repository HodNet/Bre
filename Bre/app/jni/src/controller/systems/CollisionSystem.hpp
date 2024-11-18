//
// Created by Jonathan on 30/10/2024.
//

#ifndef BRE_COLLISIONSYSTEM_HPP
#define BRE_COLLISIONSYSTEM_HPP

#include <map>

#include "../../controller/components/Rectangle.hpp"
#include "../../model/entities/Player.hpp"
#include "../../model/entities/Clone.hpp"
#include "../../model/entities/Game.hpp"
//#include "../../model/entities/Obstacle.hpp"

class CollisionSystem {

public:
    static bool checkCollision(const Rectangle& r1, const Rectangle& r2) {
        return r1.intersects(r2);
    }

    static void updatePlayerCloneCollisions(const Player* player, const std::map<int, Clone>* clones, Game* game) {
        for(auto& clone_pair : *clones) {
            if(checkCollision(player->getRect(), clone_pair.second.getRect())) {
                game->over();
            }
        }
    }

    static void updatePlayerMapMarginsCollisions(const Player* player, const Rectangle* mapSize, Game* game) {
        if(!mapSize->contains(player->getRect())) {
            game->over();
        }
    }

};

#endif //BRE_COLLISIONSYSTEM_HPP
