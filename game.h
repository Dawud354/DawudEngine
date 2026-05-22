//
// Created by dawud on 5/17/26.
//

#ifndef DAWUDENGINE_GAME_H
#define DAWUDENGINE_GAME_H

#include <SFML/Graphics.hpp>
#include "ResourceHolder.h"

// The SFML book had the namespace here
namespace Textures
{
    enum class ID
    {
        Landscape,
        Airplane,
    };
}

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
    sf::Sprite  mainPlayer;

    sf::Sprite  landscape;

    // This is here to ensure the texture it alive for the whole game
    ResourceHolder<sf::Texture, Textures::ID> textures;

    bool isMovingUp;
    bool isMovingDown;
    bool isMovingRight;
    bool isMovingLeft;
};


#endif //DAWUDENGINE_GAME_H
