//
// Created by dawud on 6/26/26.
//

#ifndef DAWUDENGINE_MENUSTATE_H
#define DAWUDENGINE_MENUSTATE_H

#include "State.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class MenuState : public State {
public:
    MenuState(StateStack &stack, Context context);

    virtual void draw();

    virtual bool update(sf::Time dt);

    virtual bool handleEvent(const sf::Event &event);

    void updateOptionText();

private:
    enum OptionNames {
        Play,
        Exit,
    };

private:
    sf::Sprite backgroundSprite;

    std::vector<sf::Text> options;
    std::size_t optionIndex;
};


#endif //DAWUDENGINE_MENUSTATE_H
