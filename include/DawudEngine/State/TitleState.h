//
// Created by dawud on 6/26/26.
//

#ifndef DAWUDENGINE_TITLESTATE_H
#define DAWUDENGINE_TITLESTATE_H

#include "State.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class TitleState : public State {
public:
    TitleState(StateStack &stack, Context context);

    void draw() override;
    bool update(sf::Time dt) override;
    bool handleEvent(const sf::Event &event) override;

private:
    sf::Sprite backgroundSprite;
    sf::Text titleText;

    bool showText;
    sf::Time textEffectTime;
};

#endif //DAWUDENGINE_TITLESTATE_H
