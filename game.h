//
// Created by dawud on 5/17/26.
//

#ifndef DAWUDENGINE_GAME_H
#define DAWUDENGINE_GAME_H

#include <SFML/Graphics.hpp>

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
    sf::Texture texture;
    sf::Sprite  mainPlayer;

    bool isMovingUp;
    bool isMovingDown;
    bool isMovingRight;
    bool isMovingLeft;
};


#endif //DAWUDENGINE_GAME_H
