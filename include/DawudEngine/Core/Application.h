//
// Created by dawud on 5/17/26.
//

#ifndef DAWUDENGINE_GAME_H
#define DAWUDENGINE_GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>

#include "PlayerInputHandler.h"
#include "ResourceHolder.h"
#include "ResourceIndentifiers.h"
#include "State/StateStack.h"


class Application{
public:
    Application();
    void run();

private:
    void processInput();
    void update(sf::Time dt);
    void render();

    void updateStatistics(sf::Time dt);
    void registerStates();

    static const sf::Time TimePerFrame;

    sf::RenderWindow mainWindow;
    TextureHolder textures;
    FontHolder fonts;
    PlayerInputHandler player;

    StateStack stateStack;

    sf::Text statisticsText;
    sf::Time statisticsUpdateTime;
    std::size_t statisticsNumFrames;
};


#endif //DAWUDENGINE_GAME_H
