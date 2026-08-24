//
// Created by dawud on 6/26/26.
//

#ifndef DAWUDENGINE_MENUSTATE_H
#define DAWUDENGINE_MENUSTATE_H

#include <SFML/Graphics/Sprite.hpp>

#include "State.h"
#include "GUI/Container.h"

class MenuState : public State {
public:
    MenuState(StateStack &stack, Context context);

    void draw() override;
    bool update(sf::Time dt) override;
    bool handleEvent(const sf::Event &event) override;

    void updateOptionText();

private:
    sf::Sprite backgroundSprite;
    GUI::Container GUIContainer;
};


#endif //DAWUDENGINE_MENUSTATE_H
