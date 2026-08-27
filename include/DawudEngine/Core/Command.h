//
// Created by dawud on 6/11/26.
//

#ifndef DAWUDENGINE_COMMAND_H
#define DAWUDENGINE_COMMAND_H

#include <SFML/System/Time.hpp>

#include <functional>
#include <cassert>


// Forward declaration. Helps avoid having to write include
class SceneNode;

struct Command
{
    // kinda cool i can make a using in a struct
    using Action = std::function<void(SceneNode&, sf::Time)>;

    Command();

    Action action;
    unsigned int category;
};

// This is used to avoid having to downcast each time we need to work on a child of SceneNode
// Bit ugly but book was right that it helps a lot later on
template <typename GameObject, typename Function>
Command::Action derivedAction(Function fn)
{
    return [=] (SceneNode& node, sf::Time dt)
    {
        // Check if cast is safe
        assert(dynamic_cast<GameObject*>(&node) != nullptr);

        // Downcast node and invoke function on it
        fn(static_cast<GameObject&>(node), dt);
    };
}

#endif //DAWUDENGINE_COMMAND_H
