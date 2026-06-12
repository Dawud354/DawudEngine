//
// Created by dawud on 6/11/26.
//

#ifndef DAWUDENGINE_COMMAND_H
#define DAWUDENGINE_COMMAND_H

#include <SFML/System/Time.hpp>

#include <functional>


// forward declaration. Helps avoid having to write include
class SceneNode;

struct Command
{
    Command();

    std::function<void(SceneNode&, sf::Time)>	action;
    unsigned int								category;
};


#endif //DAWUDENGINE_COMMAND_H
