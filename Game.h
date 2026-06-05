//
// Created by dawud on 5/17/26.
//

#ifndef DAWUDENGINE_GAME_H
#define DAWUDENGINE_GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>

#include "ResourceHolder.h"
#include "World.h"


class Game{
public:
    Game();
    void run();
private:
    void processEvents();
    void update(sf::Time dt);
    void render();
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

    static const float PlayerSpeed;
    static const sf::Time TimePerFrame;

    sf::RenderWindow mainWindow;
    World world;
};


#endif //DAWUDENGINE_GAME_H
