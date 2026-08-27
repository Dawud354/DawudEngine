//
// Created by dawud on 6/26/26.
//

#include "State/TitleState.h"
#include "Utility.h"
#include "ResourceHolder.h"

#include <SFML/Graphics/RenderWindow.hpp>


TitleState::TitleState(StateStack& stack, Context context)
: State(stack, context)
, titleText()
, showText(true)
, textEffectTime(sf::Time::Zero)
{
    backgroundSprite.setTexture(context.textures->get(Textures::TitleScreen));

    titleText.setFont(context.fonts->get(Fonts::Main));
    titleText.setString("Press any key to start");
    centerOrigin(titleText);
    titleText.setPosition(context.window->getView().getSize() / 2.f);
}

void TitleState::draw()
{
    sf::RenderWindow& window = *getContext().window;
    window.draw(backgroundSprite);

    if (showText)
        window.draw(titleText);
}

bool TitleState::update(sf::Time dt)
{
    textEffectTime += dt;

    if (textEffectTime >= sf::seconds(0.5f))
    {
        showText = !showText;
        textEffectTime = sf::Time::Zero;
    }

    return true;
}

bool TitleState::handleEvent(const sf::Event& event)
{
    // If any key is pressed, trigger the next screen
    if (event.type == sf::Event::KeyPressed)
    {
        requestStackPop();
        requestStackPush(States::Menu);
    }

    return true;
}