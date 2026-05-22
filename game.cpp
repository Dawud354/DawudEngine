//
// Created by dawud on 5/17/26.
// This is the main loop of the engine
//

#include "game.h"
#include "ResourceHolder.h"

#include <iostream>


// set the constants here
// not sure why here but the SFMl game dev book did it here
const float Game::PlayerSpeed = 100.f;
const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);


Game::Game()
: mainWindow(sf::VideoMode(640, 480), "SFML Application")
, mainPlayer()
, isMovingUp(false)
, isMovingDown(false)
, isMovingRight(false)
, isMovingLeft(false)
{
    std::cout << "making class" << std::endl;

    // try load resources
    try
    {
        textures.load(Textures::ID::Landscape, "Media/Textures/Desert.png");
        textures.load(Textures::ID::Airplane, "Media/Textures/Eagle.png");
    }
    catch (std::runtime_error& e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
        return;
    }

    // load the plane texture to the mainPlayer
    mainPlayer.setTexture(textures.get(Textures::ID::Airplane));
    mainPlayer.setPosition(100.f, 100.f);
}

/*
 * Used to start the engine
 */
void Game::run()
{
    std::cout << "in the game class" << std::endl;




    // make a clock so we can track the time between each frame
    sf::Clock clock;

    // this line is to make the update logic update at a fixed interval to avoid issues with B
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (mainWindow.isOpen())
    {
        // this outer call is to help with responsiveness
        // say we pressed the close button if we only had the inner one it would take 16.6ms to
        // respond which can feel slow to a user
        processEvents();
        timeSinceLastUpdate += clock.restart();

        while (timeSinceLastUpdate > TimePerFrame) {
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();
            update(TimePerFrame);
        }
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

