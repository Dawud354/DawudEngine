//
// Created by dawud on 6/26/26.
//

#ifndef DAWUDENGINE_PAUSESTATE_H
#define DAWUDENGINE_PAUSESTATE_H

#include "State.h"
#include "GUI/Container.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class PauseState : public State {
public:
    PauseState(StateStack &stack, Context context);

    void draw() override;
    bool update(sf::Time dt) override;
    bool handleEvent(const sf::Event &event) override;

private:
    sf::Sprite backgroundSprite;
    sf::Text pausedText;
    GUI::Container GUIContainer;
};


#endif //DAWUDENGINE_PAUSESTATE_H
