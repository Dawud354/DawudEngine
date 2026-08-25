//
// Created by dawud on 6/12/26.
//

#ifndef DAWUDENGINE_PLAYERINPUTHANDLER_H
#define DAWUDENGINE_PLAYERINPUTHANDLER_H
#include <map>
#include <SFML/Window/Event.hpp>
#include "CommandQueue.h"


class PlayerInputHandler {
public:
    enum class Action{
        MoveLeft,
        MoveRight,
        MoveUp,
        MoveDown,
        Fire,
        LaunchMissile,
        ActionCount
    };

    enum class MissionStatus
    {
        MissionRunning,
        MissionSuccess,
        MissionFailure
    };

    PlayerInputHandler();

    void handleEvent(const sf::Event& event, CommandQueue& commands);
    void handleRealTimeInput(CommandQueue& commands);

    void assignKey(Action action, sf::Keyboard::Key key);
    sf::Keyboard::Key getAssignedKey(Action action) const;

    void setMissionStatus(MissionStatus status);
    MissionStatus getMissionStatus() const;

private:
    void initialiseActions();
    // reason it is static is cos in C++ a convention is to label helper
    // functions as static to indicate they do not edit the object
    static bool isRealTimeAction(Action action);

    std::map<sf::Keyboard::Key, Action> keyBinding;
    std::map<Action, Command> actionBinding;
    MissionStatus currentMissionStatus;
};


#endif //DAWUDENGINE_PLAYERINPUTHANDLER_H
