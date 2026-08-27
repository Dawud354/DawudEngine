//
// Created by dawud on 6/12/26.
//

#include "PlayerInputHandler.h"
#include "Aircraft.h"
#include "CommandQueue.h"

#include <map>


// not sure why this is here the book had it here
struct AircraftMover
{
    AircraftMover(float vx, float vy)
    : velocity(vx, vy)
    {
    }

    void operator() (Aircraft& aircraft, sf::Time) const
    {
        aircraft.accelerate(velocity * aircraft.getMaxSpeed());
    }

    sf::Vector2f velocity;
};

PlayerInputHandler::PlayerInputHandler()
    : currentMissionStatus(MissionStatus::MissionRunning) {
    // set initial key binding
    keyBinding[sf::Keyboard::Left] = Action::MoveLeft;
    keyBinding[sf::Keyboard::Right] = Action::MoveRight;
    keyBinding[sf::Keyboard::Up] = Action::MoveUp;
    keyBinding[sf::Keyboard::Down] = Action::MoveDown;
    keyBinding[sf::Keyboard::Space] = Action::Fire;
    keyBinding[sf::Keyboard::M] = Action::LaunchMissile;

    // set the action bindings
    initialiseActions();

    // assign all categories to the players aircraft
    for (auto& pair : actionBinding) {
        pair.second.category = Category::PlayerAircraft;
    }
}

void PlayerInputHandler::handleEvent(const sf::Event& event, CommandQueue& commands)
{
    if (event.type == sf::Event::KeyPressed)
    {
        // Check if pressed key appears in key binding, trigger command if so
        auto found = keyBinding.find(event.key.code);
        if (found != keyBinding.end() && !isRealTimeAction(found->second))
            commands.push(actionBinding[found->second]);
    }
}

void PlayerInputHandler::handleRealTimeInput(CommandQueue& commands)
{
    // Traverse all assigned keys and check if they are pressed
    for(auto& pair: keyBinding)
    {
        // If key is pressed, lookup action and trigger corresponding command
        if (sf::Keyboard::isKeyPressed(pair.first) && isRealTimeAction(pair.second))
            commands.push(actionBinding[pair.second]);
    }
}

void PlayerInputHandler::assignKey(Action action, sf::Keyboard::Key key) {
    // remove all keys that already map to this action
    // I originally tried to use a for each loop but it didn't work
    // cos removing items while doing for each can lead to issues
    // so I used the way the book did it
    for (auto itr = keyBinding.begin(); itr != keyBinding.end();) {
        if (itr->second == action)
            keyBinding.erase(itr++);
        else
            ++itr;
    }
    // Insert new binding
    keyBinding[key] = action;
}

sf::Keyboard::Key PlayerInputHandler::getAssignedKey(Action action) const {
    for (auto pair : keyBinding) {
        if (pair.second == action)
            return pair.first;
    }

    return sf::Keyboard::Unknown;
}

void PlayerInputHandler::setMissionStatus(MissionStatus status) {
    currentMissionStatus = status;
}

PlayerInputHandler::MissionStatus PlayerInputHandler::getMissionStatus() const {
    return currentMissionStatus;
}

void PlayerInputHandler::initialiseActions() {
    actionBinding[Action::MoveLeft].action = derivedAction<Aircraft>(AircraftMover(-1,0));
    actionBinding[Action::MoveRight].action = derivedAction<Aircraft>(AircraftMover(+1,0));
    actionBinding[Action::MoveUp].action = derivedAction<Aircraft>(AircraftMover(0,-1));
    actionBinding[Action::MoveDown].action = derivedAction<Aircraft>(AircraftMover(0,+1));
    actionBinding[Action::Fire].action = derivedAction<Aircraft>([] (Aircraft& a, sf::Time) {a.fire();});
    actionBinding[Action::LaunchMissile].action = derivedAction<Aircraft>([] (Aircraft& a, sf::Time) {a.launchMissie();});
}

bool PlayerInputHandler::isRealTimeAction(Action action) {
    switch (action) {
        case Action::MoveLeft:
        case Action::MoveRight:
        case Action::MoveUp:
        case Action::MoveDown:
        case Action::Fire:
            return true;
        default:
            return false;
    }
}


