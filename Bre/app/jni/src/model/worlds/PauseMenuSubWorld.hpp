//
// Created by Jonathan on 14/11/2024.
//

#ifndef BRE_PAUSEMENUSUBWORLD_HPP
#define BRE_PAUSEMENUSUBWORLD_HPP

#include "../../res/images.hpp"
#include "../../res/dimens.hpp"
#include "../../res/strings.hpp"
#include "../../model/worlds/SubWorld.hpp"
#include "../../model/worlds/GameWorld.hpp"
#include "../../model/states/SubWorldState.hpp"
#include "../../controller/components/Transition_VerticalOscillation.hpp"
#include "../../controller/components/DisplacementAnimation.hpp"
#include "../../controller/components/Text.hpp"
#include "../../controller/components/Image.hpp"
#include "../../controller/components/IconButton.hpp"
#include "../../controller/components/TouchInput.hpp"

class PauseMenuSubWorld : virtual public SubWorld {

private:
    GameWorld* gameWorld;
    SubWorldState pauseMenuSubWorldState = SubWorldState::ENTERING;

    // Transitions
    static Transition_VerticalOscillation* enterTransition;
    static DisplacementAnimation* exitTransition;

    // Entities
    static Text* title;
    static Image* background;

    // Buttons
    static IconButton* resumeButton;
    static IconButton* restartButton;
    static IconButton* exitButton;
    static IconButton* cancelButton;

public:
    PauseMenuSubWorld(GameWorld& gameWorld) : gameWorld(&gameWorld) {}

    void enter(unsigned int screen_w, unsigned int screen_h) override {
        background = new Image(
                screen_w / 2 - dimens::pause_menu_background_width / 2,
                screen_h / 2 - dimens::pause_menu_background_height / 2,
                dimens::pause_menu_background_width,
                dimens::pause_menu_background_height,
                images::menu_background,
                dimens::pause_menu_background_file_width,
                dimens::pause_menu_background_file_height
        );
        enterTransition = new Transition_VerticalOscillation(*background, -dimens::pause_menu_background_height);
        exitTransition = new DisplacementAnimation(background->y, screen_h+dimens::pause_menu_background_height);
        title = new Text(
                screen_w / 2,
                background->Ymax() - background->h/4,
                strings::pause_menu_title,
                dimens::huge_title_font_size,
                true
        );
        resumeButton = new IconButton(
                background->Xmax() - dimens::large_icon_button_size - dimens::horizontal_margin,
                background->Ymin() + dimens::vertical_margin,
                dimens::large_icon_button_size,
                dimens::large_icon_button_size,
                images::resume_button,
                dimens::resume_button_file_width,
                dimens::resume_button_file_height
        );
        restartButton = new IconButton(
                background->Xmin() + dimens::horizontal_margin,
                background->Ymin() + dimens::vertical_margin,
                dimens::large_icon_button_size,
                dimens::large_icon_button_size,
                images::restart_button,
                dimens::restart_button_file_width,
                dimens::restart_button_file_height
        );
        exitButton = new IconButton(
                screen_w / 2 - dimens::large_icon_button_size / 2,
                background->Ymin() + dimens::vertical_margin,
                dimens::large_icon_button_size,
                dimens::large_icon_button_size,
                images::exit_button,
                dimens::exit_button_file_width,
                dimens::exit_button_file_height
        );
        cancelButton = new IconButton(
                background->Xmax() - dimens::small_icon_button_size - dimens::horizontal_margin,
                background->Ymax() - dimens::small_icon_button_size - dimens::vertical_margin,
                dimens::small_icon_button_size,
                dimens::small_icon_button_size,
                images::cancel_button,
                dimens::cancel_button_file_width,
                dimens::cancel_button_file_height
        );

        resumeButton->setOnClickListener([&]() {
            pauseMenuSubWorldState = SubWorldState::EXITING;
        });
        restartButton->setOnClickListener([&]() {
            pauseMenuSubWorldState = SubWorldState::EXITING;
            gameWorld->reset();
        });
        exitButton->setOnClickListener([&]() {
            pauseMenuSubWorldState = SubWorldState::EXITING;
            gameWorld->exit();
        });
        cancelButton->setOnClickListener([&]() {
            pauseMenuSubWorldState = SubWorldState::EXITING;
        });
    }

    void update() override {
        SDL_Log("State: %d", pauseMenuSubWorldState);
        switch (pauseMenuSubWorldState) {
            case SubWorldState::ENTERING:
                if (enterTransition->isFinished()) {
                    pauseMenuSubWorldState = SubWorldState::ENTERED;
                } else {
                    enterTransition->update();
                    title->setY(background->Ymax() - background->h/4);
                    resumeButton->setY(background->Ymin() + dimens::vertical_margin);
                    restartButton->setY(background->Ymin() + dimens::vertical_margin);
                    exitButton->setY(background->Ymin() + dimens::vertical_margin);
                    cancelButton->setY(background->Ymax() - dimens::small_icon_button_size - dimens::vertical_margin);
                }
                break;
            case SubWorldState::ENTERED:
                break;
            case SubWorldState::EXITING:
                if (exitTransition->isFinished()) {
                    gameWorld->resume();
                    exit();
                } else {
                    exitTransition->update();
                    title->setY(background->Ymax() - background->h/4);
                    resumeButton->setY(background->Ymin() + dimens::vertical_margin);
                    restartButton->setY(background->Ymin() + dimens::vertical_margin);
                    exitButton->setY(background->Ymin() + dimens::vertical_margin);
                    cancelButton->setY(background->Ymax() - dimens::small_icon_button_size - dimens::vertical_margin);
                }
                break;
            case SubWorldState::EXITED:
                break;
        }
    }

    void handleInput(TouchInput* touchInput) override {
        resumeButton->handleInput(touchInput);
        restartButton->handleInput(touchInput);
        exitButton->handleInput(touchInput);
        cancelButton->handleInput(touchInput);
        delete touchInput;
    }

    void exit() override {
        delete enterTransition; enterTransition = nullptr;
        delete exitTransition; exitTransition = nullptr;
        delete title; title = nullptr;
        delete background; background = nullptr;
        delete resumeButton; resumeButton = nullptr;
        delete restartButton; restartButton = nullptr;
        delete exitButton; exitButton = nullptr;
        delete cancelButton; cancelButton = nullptr;
        pauseMenuSubWorldState = SubWorldState::EXITED;
    }

    bool isExited() const {
        return pauseMenuSubWorldState == SubWorldState::EXITED;
    }

    static Text* getTitle() {
        return title;
    }

    static Image* getBackground() {
        return background;
    }

    static IconButton* getResumeButton() {
        return resumeButton;
    }

    static IconButton* getRestartButton() {
        return restartButton;
    }

    static IconButton* getExitButton() {
        return exitButton;
    }

    static IconButton* getCancelButton() {
        return cancelButton;
    }
};

#endif //BRE_PAUSEMENUSUBWORLD_HPP
