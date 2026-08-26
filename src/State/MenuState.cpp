//
// Created by dawud on 6/26/26.
//

#include "State/MenuState.h"
#include "Utility.h"
#include "ResourceHolder.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

#include "GUI/Button.h"
#include "State/StateIdentifiers.h"


MenuState::MenuState(StateStack& stack, Context context)
: State(stack, context)
, GUIContainer()
{
	sf::Texture& texture = context.textures->get(Textures::TitleScreen);
	sf::Font& font = context.fonts->get(Fonts::Main);

	backgroundSprite.setTexture(texture);

	auto playButton  = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	playButton-> setPosition(100,300);
	playButton->setText("Play");
	playButton->setCallback( [this] () {
		requestStackPop();
		requestStackPush(States::Game);
	});

	auto settingsButton  = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	settingsButton-> setPosition(100,350);
	settingsButton->setText("Settings");
	settingsButton->setCallback( [this] () {
		requestStackPush(States::Settings);
	});

	auto exitButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	exitButton->setPosition(100, 400);
	exitButton->setText("Exit");
	exitButton->setCallback([this] ()
	{
		requestStackPop();
	});

	GUIContainer.pack(playButton);
	GUIContainer.pack(settingsButton);
	GUIContainer.pack(exitButton);
}

void MenuState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());

	window.draw(backgroundSprite);
	window.draw(GUIContainer);
}

bool MenuState::update(sf::Time)
{
	return true;
}

bool MenuState::handleEvent(const sf::Event& event)
{
	GUIContainer.handleEvent(event);
	return false;
}
