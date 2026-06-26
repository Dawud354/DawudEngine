//
// Created by dawud on 6/26/26.
//

#include "GameState.h"

GameState::GameState(StateStack& stack, Context context)
: State(stack, context)
, world(*context.window)
, player(*context.player)
{
}

void GameState::draw()
{
    world.draw();
}

bool GameState::update(sf::Time dt)
{
    world.update(dt);

    CommandQueue& commands = world.getCommandQueue();
    player.handleRealTimeInput(commands);

    return true;
}

bool GameState::handleEvent(const sf::Event& event)
{
    // Game input handling
    CommandQueue& commands = world.getCommandQueue();
    player.handleEvent(event, commands);

    // Escape pressed, trigger the pause screen
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        requestStackPush(States::Pause);

    return true;
}