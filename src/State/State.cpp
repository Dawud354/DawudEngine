//
// Created by dawud on 6/25/26.
//

#include "State/State.h"
#include "State/StateStack.h"

State::Context::Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, PlayerInputHandler& player)
: window(&window)
, textures(&textures)
, fonts(&fonts)
, player(&player)
{
}

State::State(StateStack& stack, Context context)
: stack(&stack)
, context(context)
{
}

State::~State()
{
}

void State::requestStackPush(States::ID stateID)
{
    stack->pushState(stateID);
}

void State::requestStackPop()
{
    stack->popState();
}

void State::requestStateClear()
{
    stack->clearStates();
}

State::Context State::getContext() const
{
    return context;
}