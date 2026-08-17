//
// Created by dawud on 6/12/26.
//

#include "../../include/DawudEngine/Core/PlayerInputHandler.h"
#include "Aircraft.h"

// not sure why this is here the book had it here
// the point of this is to like make an executable struct that we can make a n ac
struct AircraftMover
{
    AircraftMover(float vx, float vy)
    : velocity(vx, vy)
    {
    }

    void operator() (Aircraft& aircraft, sf::Time) const
    {
        aircraft.accelerate(velocity);
    }

    sf::Vector2f velocity;
};

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
    for(auto pair: keyBinding)
    {
        // If key is pressed, lookup action and trigger corresponding command
        if (sf::Keyboard::isKeyPressed(pair.first) && isRealTimeAction(pair.second))
            commands.push(actionBinding[pair.second]);
    }
}
