//
// Created by dawud on 5/17/26.
// This is the main loop of the engine
//

#include "Application.h"

#include <iostream>

#include "GameOverState.h"
#include "Utility.h"
#include "State/GameState.h"
#include "State/MenuState.h"
#include "State/PauseState.h"
#include "State/SettingsState.h"
#include "State/State.h"
#include "State/TitleState.h"


// set the constants here
// not sure why here but the SFMl game dev book did it here
const sf::Time Application::TimePerFrame = sf::seconds(1.f/60.f);


Application::Application()
: mainWindow(sf::VideoMode(1024, 768), "SFML Application", sf::Style::Close)
, textures()
, fonts()
, player()
, stateStack(State::Context(mainWindow, textures, fonts, player))
, statisticsText()
, statisticsUpdateTime()
, statisticsNumFrames(0)
{
    //I think this is to stop me spamming fire
    mainWindow. setKeyRepeatEnabled(false);

    fonts.load(Fonts::Main, "Media/Sansation.ttf");

    textures.load(Textures::TitleScreen, "Media/Textures/TitleScreen.png");
    textures.load(Textures::ButtonNormal,"Media/Textures/ButtonNormal.png");
    textures.load(Textures::ButtonSelected,"Media/Textures/ButtonSelected.png");
    textures.load(Textures::ButtonPressed,"Media/Textures/ButtonPressed.png");

    statisticsText.setFont(fonts.get(Fonts::Main));
    statisticsText.setPosition(5.f, 5.f);
    statisticsText.setCharacterSize(10u);

    registerStates();
    stateStack.pushState(States::Title);


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

        const sf::Time dt = clock.restart();
        timeSinceLastUpdate += dt;
        while (timeSinceLastUpdate > TimePerFrame) {
            timeSinceLastUpdate -= TimePerFrame;
            processInput();
            update(TimePerFrame);

            // check inside this loop cos stack might be empty before update() call
            if (stateStack.isEmpty()) {
                mainWindow.close();
            }
        }
        updateStatistics(dt);
        render();
    }
}

void Application::processInput() {
    sf::Event e;
    while (mainWindow.pollEvent(e)) {
        stateStack.handleEvent(e);

        if (e.type == sf::Event::Closed)
            mainWindow.close();
    }
}

void Application::update(sf::Time dt){
    stateStack.update(dt);
}

void Application::render() {
    mainWindow.clear();

    stateStack.draw();

	mainWindow.setView(mainWindow.getDefaultView());
    mainWindow.draw(statisticsText);

    mainWindow.display();
}

void Application::updateStatistics(sf::Time dt) {
    statisticsUpdateTime += dt;
    statisticsNumFrames += 1;
    if (statisticsUpdateTime > sf::seconds(1.0f)) {
        statisticsText.setString("FPS: " + std::to_string((statisticsNumFrames)));

        statisticsUpdateTime -= sf::seconds(1.0f);
        statisticsNumFrames = 0;
    }
}
void Application::registerStates() {
    stateStack.registerState<TitleState>(States::Title);
    stateStack.registerState<MenuState>(States::Menu);
    stateStack.registerState<GameState>(States::Game);
    stateStack.registerState<PauseState>(States::Pause);
    stateStack.registerState<SettingsState>(States::Settings);
    stateStack.registerState<GameOverState>(States::GameOver);
}

