//
// Created by dawud on 5/17/26.
// This is the main loop of the engine
//

#include "game.h"

#include <iostream>


// set the constants here
// not sure why here but the SFMl game dev book did it here
const float Game::PlayerSpeed = 100.f;

Game::Game()
: mainWindow(sf::VideoMode(640, 480), "SFML Application")
, mainPlayer()
, isMovingUp(false)
, isMovingDown(false)
, isMovingRight(false)
, isMovingLeft(false)
{
    std::cout << "making class" << std::endl;

    mainPlayer.setRadius(40.f);
    mainPlayer.setPosition(100.f, 100.f);
    mainPlayer.setFillColor(sf::Color::Cyan);
}

/*
 * Used to start the engine
 */
void Game::run()
{
    std::cout << "in the game class" << std::endl;

    // make a clock so we can track the time between each frame
    sf::Clock clock;
    while (mainWindow.isOpen())
    {
        sf::Time dt = clock.restart();
        processEvents();
        update(dt);
        render();
    }
}

void Game::processEvents() {
    sf::Event e;
    while (mainWindow.pollEvent(e)) {
        switch (e.type) {
            case sf::Event::KeyPressed:
                handlePlayerInput(e.key.code, true);
                break;
            case sf::Event::KeyReleased:
                handlePlayerInput(e.key.code, false);
                break;
            case sf::Event::Closed:
                mainWindow.close();
                break;
            default:
                break;
        }
    }
}

void Game::update(sf::Time dt){
    sf::Vector2f movement(0.f, 0.f);
    if (isMovingUp)
        movement.y -= PlayerSpeed;
    if (isMovingDown)
        movement.y += PlayerSpeed;
    if (isMovingLeft)
        movement.x -= PlayerSpeed;
    if (isMovingRight)
        movement.x += PlayerSpeed;
    mainPlayer.move(movement * dt.asSeconds());
}

void Game::render() {
    mainWindow.clear();
    mainWindow.draw(mainPlayer);
    mainWindow.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
    if (key == sf::Keyboard::W)
        isMovingUp = isPressed;
    if (key == sf::Keyboard::S)
        isMovingDown = isPressed;
    if (key == sf::Keyboard::A)
        isMovingLeft = isPressed;
    if (key == sf::Keyboard::D)
        isMovingRight = isPressed;
}

