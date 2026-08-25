//
// Created by dawud on 6/26/26.
//

#include "State/GameState.h"

GameState::GameState(StateStack& stack, Context context)
: State(stack, context)
, world(*context.window)
, player(*context.player)
{
    player.setMissionStatus(PlayerInputHandler::MissionStatus::MissionRunning);
}

void GameState::draw()
{
    world.draw();
}
// clion was being weird and didn't recognised requestStatePush as I was typing
bool GameState::update(sf::Time dt)
{
    world.update(dt);

    if (!world.hasAlivePlayer()) {
        player.setMissionStatus(PlayerInputHandler::MissionStatus::MissionFailure);
        requestStackPush(States::GameOver);
    } else if (world.hasPlayerReachedEnd()) {
        player.setMissionStatus(PlayerInputHandler::MissionStatus::MissionSuccess);
        requestStackPush(States::GameOver);
    }

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