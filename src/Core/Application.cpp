//
// Created by dawud on 5/17/26.
// This is the main loop of the engine
//

#include "Application.h"
#include "ResourceHolder.h"

#include <iostream>


// set the constants here
// not sure why here but the SFMl game dev book did it here
const float Application::PlayerSpeed = 100.f;
const sf::Time Application::TimePerFrame = sf::seconds(1.f/60.f);


Application::Application()
: mainWindow(sf::VideoMode(640, 480), "SFML Application")
, world(mainWindow)
{
}

/*
 * Used to start the engine
 */
void Application::run()
{
    // make a clock so we can track the time between each frame
    sf::Clock clock;

    // this line is to make the update logic update at a fixed interval to avoid issues with B
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (mainWindow.isOpen())
    {
        // this outer call is to help with responsiveness
        // say we pressed the close button if we only had the inner one it would take 16.6ms to
        // respond which can feel slow to a user
        // ---------------------------------------
        // in Chapter 3 the book seemed to remove it but I will keep it commented for now
        //processEvents();
        timeSinceLastUpdate += clock.restart();

        while (timeSinceLastUpdate > TimePerFrame) {
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();
            update(TimePerFrame);
        }
        render();
    }
}

void Application::processEvents() {
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

void Application::update(sf::Time dt){
    world.update(dt);
}

void Application::render() {
    mainWindow.clear();
    world.draw();

	mainWindow.setView(mainWindow.getDefaultView());
    mainWindow.display();
}

void Application::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
}

