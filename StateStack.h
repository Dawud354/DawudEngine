//
// Created by dawud on 6/25/26.
//

#ifndef DAWUDENGINE_STATESTACK_H
#define DAWUDENGINE_STATESTACK_H

#include "State.h"
#include "StateIdentifiers.h"
#include "ResourceIndentifiers.h"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>

#include <vector>
#include <utility>
#include <functional>
#include <map>


namespace sf {
    class Event;
    class RenderWindow;
}

class StateStack : private sf::NonCopyable {
public:
    enum Action {
        Push,
        Pop,
        Clear,
    };

    explicit StateStack(State::Context context);

    template<typename T>
    void registerState(States::ID stateID);

    void update(sf::Time dt);

    void draw();

    void handleEvent(const sf::Event &event);

    void pushState(States::ID stateID);

    void popState();

    void clearStates();

    bool isEmpty() const;

private:
    State::UniquePtr createState(States::ID stateID);

    void applyPendingChanges();


    struct PendingChange {
        explicit PendingChange(Action action, States::ID stateID = States::None);

        Action action;
        States::ID stateID;
    };


    std::vector<State::UniquePtr> stack;
    std::vector<PendingChange> pendingList;

    State::Context context;
    std::map<States::ID, std::function<State::UniquePtr()> > factories;
};


template<typename T>
void StateStack::registerState(States::ID stateID) {
    factories[stateID] = [this]() {
        return State::UniquePtr(new T(*this, context));
    };
}


#endif //DAWUDENGINE_STATESTACK_H
