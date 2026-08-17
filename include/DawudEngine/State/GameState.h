//
// Created by dawud on 6/26/26.
//

#ifndef DAWUDENGINE_GAMESTATE_H
#define DAWUDENGINE_GAMESTATE_H

#include "../State.h"
#include "World.h"
#include "PlayerInputHandler.h"

class GameState : public State
{
public:
    GameState(StateStack& stack, Context context);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);


private:
    World world;
    PlayerInputHandler& player;
};


#endif //DAWUDENGINE_GAMESTATE_H
