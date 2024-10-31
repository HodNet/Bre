//
// Created by Jonathan on 11/10/2024.
//

#ifndef BRE_INGAMEEVENTSYSTEM_HPP
#define BRE_INGAMEEVENTSYSTEM_HPP

enum class InGameEvent {
    START_GAME,
    START_PLAYER_MOVEMENT,
    STOP_PLAYER_MOVEMENT
};

class InGameEventSystem {

public:
    static void handleEvent(InGameEvent event);
};

#endif //BRE_INGAMEEVENTSYSTEM_HPP
