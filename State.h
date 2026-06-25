//
// Created by dawud on 6/25/26.
//

#ifndef DAWUDENGINE_STATE_H
#define DAWUDENGINE_STATE_H


#include "ResourceIndentifiers.h"
#include "StateIdentifiers.h"

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include <memory>

// forward declaration
namespace sf
{
    class RenderWindow;
}

class StateStack;
class Player;

class State
{
public:
    using UniquePtr =  std::unique_ptr<State>;

    // i think this just stores pointers to the stuff in my game
    // i did not really get into the nitty gritty of chapter 5 just enough to understand
    // what a the
    struct Context
    {
        Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, Player& player);

        sf::RenderWindow* window;
        TextureHolder* textures;
        FontHolder* fonts;
        Player* player;
    };

    State(StateStack& stack, Context context);
    virtual ~State();

    virtual void draw() = 0;
    virtual bool update(sf::Time dt) = 0;
    virtual bool handleEvent(const sf::Event& event) = 0;


protected:
    void requestStackPush(States::ID stateID);
    void requestStackPop();
    void requestStateClear();

    Context getContext() const;


private:
    StateStack* stack;
    Context context;
};


#endif //DAWUDENGINE_STATE_H
