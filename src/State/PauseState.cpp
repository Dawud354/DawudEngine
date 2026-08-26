//
// Created by dawud on 6/26/26.
//

#include "State/PauseState.h"
#include "Utility.h"
#include "ResourceHolder.h"
#include "GUI/Button.h"
#include "State/StateIdentifiers.h"


#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>


PauseState::PauseState(StateStack& stack, Context context)
: State(stack, context)
, backgroundSprite()
, pausedText()
, GUIContainer()
{
    sf::Font& font = context.fonts->get(Fonts::Main);
    sf::Vector2f windowSize (context.window->getSize());

    pausedText.setFont(font);
    pausedText.setString("Game Paused");
    pausedText.setCharacterSize(70);
    centerOrigin(pausedText);
    pausedText.setPosition(0.5f * windowSize.x, 0.4f * windowSize.y);

    auto returnButton  = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    returnButton-> setPosition(0.5f * windowSize.x - 100, 0.4f * windowSize.y + 75);
    returnButton->setText("Return");
    returnButton->setCallback( [this] () {
        requestStackPop();
    });

    auto backToMenuButton  = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    backToMenuButton-> setPosition(0.5f * windowSize.x - 100, 0.4f * windowSize.y + 125);
    backToMenuButton->setText("Back to Menu");
    backToMenuButton->setCallback( [this] () {
        requestStateClear();
        requestStackPush(States::Menu);
    });
}

void PauseState::draw()
{
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());

    sf::RectangleShape backgroundShape;
    backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
    backgroundShape.setSize(window.getView().getSize());

    window.draw(backgroundShape);
    window.draw(pausedText);
    window.draw(GUIContainer);
}

bool PauseState::update(sf::Time)
{
    return false;
}

bool PauseState::handleEvent(const sf::Event& event)
{
    GUIContainer.handleEvent(event);
    return false;
}