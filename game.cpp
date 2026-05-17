//
// Created by dawud on 5/17/26.
// This is the main loop of the engine
//

#include "game.h"

#include <iostream>



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

    while (mainWindow.isOpen())
    {
        processEvents();
        update();
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

void Game::update() {
    sf::Vector2f movement(0.f, 0.f);
    if (isMovingUp)
        movement.y -= 1.f;
    if (isMovingDown)
        movement.y += 1.f;
    if (isMovingLeft)
        movement.x -= 1.f;
    if (isMovingRight)
        movement.x += 1.f;
    mainPlayer.move(movement);
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

