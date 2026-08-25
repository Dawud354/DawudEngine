//
// Created by dawud on 8/24/26.
//

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>


#include "GameOverState.h"
#include "ResourceHolder.h"
#include "Utility.h"
#include "PlayerInputHandler.h"
#include "State/StateIdentifiers.h"

GameOverState::GameOverState(StateStack &stack, Context context)
    : State(stack, context)
    , gameOverText()
    , elapsedTime(sf::Time::Zero) {

    const sf::Font& font = context.fonts->get(Fonts::Main);
    sf::Vector2f windowSize( context.window->getSize());

    gameOverText.setFont(font);
    if (context.player->getMissionStatus() == PlayerInputHandler::MissionStatus::MissionFailure)
        gameOverText.setString("Mission Failed");
    else
        gameOverText.setString("Mission Successful!");

    gameOverText.setCharacterSize(70);
    centerOrigin(gameOverText);
    gameOverText.setPosition(0.5f * windowSize.x, 0.4f * windowSize.y);
}

void GameOverState::draw() {
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());

    // create dark semi transparent background
    sf::RectangleShape backgroundShape;
    backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
    backgroundShape.setSize(window.getView().getSize());

    window.draw(backgroundShape);
    window.draw(gameOverText);
}

bool GameOverState::update(sf::Time dt) {
    // show state for 4 seconds, then go back to home
    elapsedTime+=dt;
    if (elapsedTime > sf::seconds(4)) {
        requestStateClear();
        requestStackPush(States::Menu);
    }
    return false;
}

bool GameOverState::handleEvent(const sf::Event &event) {
    return false;
}
