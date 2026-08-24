//
// Created by dawud on 8/24/26.
//

#ifndef DAWUDENGINE_SETTINGSSTATE_H
#define DAWUDENGINE_SETTINGSSTATE_H

#include "State.h"
#include "PlayerInputHandler.h"
#include "GUI/Container.h"
#include "GUI/Button.h"
#include "GUI/Label.h"


#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <array>


class SettingsState : public State {
public:
    SettingsState(StateStack &stack, Context context);

    void draw() override;
    bool update(sf::Time dt) override;
    bool handleEvent(const sf::Event &event) override;

private:
    void updateLabels();
    void addButtonLabel(PlayerInputHandler::Action action, float y, const std::string &text, Context context);

    sf::Sprite mBackgroundSprite;
    GUI::Container mGUIContainer;

    // I added the using so the lines below wouldn't be so long and hard to read
    using Action = PlayerInputHandler::Action;
    std::array<GUI::Button::SharedPtr, static_cast<int>(Action::ActionCount)> mBindingButtons;
    std::array<GUI::Label::SharedPtr, static_cast<int>(Action::ActionCount)> mBindingLabels;
};


#endif //DAWUDENGINE_SETTINGSSTATE_H
