//
// Created by dawud on 6/26/26.
//

#ifndef DAWUDENGINE_UTILITY_H
#define DAWUDENGINE_UTILITY_H

#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>

#include <string>


namespace sf
{
    class Sprite;
    class Text;
}

// Convert key to strings
std::string		toString(sf::Keyboard::Key key);

void centerOrigin(sf::Sprite& sprite);
void centerOrigin(sf::Text& text);

// Degree/radian conversion
float			toDegree(float radian);
float			toRadian(float degree);

// Random number generation
int				randomInt(int exclusiveMax);

// Vector operations
float			length(sf::Vector2f vector);
sf::Vector2f	unitVector(sf::Vector2f vector);

#endif //DAWUDENGINE_UTILITY_H
