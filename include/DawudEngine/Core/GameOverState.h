//
// Created by dawud on 8/24/26.
//

#ifndef DAWUDENGINE_GAMEOVERSTATE_H
#define DAWUDENGINE_GAMEOVERSTATE_H

#include <SFML/Graphics/Text.hpp>

#include "State/State.h"

class GameOverState : public State {
public:
    GameOverState(StateStack &stack, Context context);

    void draw() override;
    bool update(sf::Time dt) override;
    bool handleEvent(const sf::Event &event) override;

private:
    sf::Text gameOverText;
    sf::Time elapsedTime;
};


#endif //DAWUDENGINE_GAMEOVERSTATE_H
