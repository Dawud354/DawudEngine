//
// Created by dawud on 6/25/26.
//

#include "State//StateStack.h"

#include <cassert>
#include <ranges>


StateStack::StateStack(State::Context context)
: stack()
, pendingList()
, context(context)
, factories()
{
}

void StateStack::update(sf::Time dt)
{
    // Iterate from top to bottom, stop as soon as update() returns false
    // cannot use for each as we are going from beginning to end
    for (const auto & itr : std::views::reverse(stack))
    {
        if (!itr->update(dt))
            break;
    }

    applyPendingChanges();
}

void StateStack::draw()
{
    // Draw all active states from bottom to top
    for(const State::UniquePtr& state: stack)
        state->draw();
}

void StateStack::handleEvent(const sf::Event& event)
{
    // Iterate from top to bottom, stop as soon as handleEvent() returns false
    for (const auto & itr : std::views::reverse(stack))
    {
        if (!itr->handleEvent(event))
            break;
    }

    applyPendingChanges();
}

void StateStack::pushState(States::ID stateID)
{
    pendingList.emplace_back(Push, stateID);
}

void StateStack::popState()
{
    pendingList.emplace_back(Pop);
}

void StateStack::clearStates()
{
    pendingList.emplace_back(Clear);
}

bool StateStack::isEmpty() const
{
    return stack.empty();
}

State::UniquePtr StateStack::createState(States::ID stateID)
{
    auto found = factories.find(stateID);
    assert(found != factories.end());

    return found->second();
}

void StateStack::applyPendingChanges()
{
    for (const PendingChange change :  pendingList)
    {
        switch (change.action)
        {
            case Push:
                stack.push_back(createState(change.stateID));
                break;

            case Pop:
                stack.pop_back();
                break;

            case Clear:
                stack.clear();
                break;
        }
    }

    pendingList.clear();
}

StateStack::PendingChange::PendingChange(Action action, States::ID stateID)
: action(action)
, stateID(stateID)
{
}