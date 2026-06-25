//
// Created by dawud on 6/5/26.
//

#ifndef DAWUDENGINE_RESOURCEINDENTIFIERS_H
#define DAWUDENGINE_RESOURCEINDENTIFIERS_H

// the SFML book did this
// might need to rear

// Forward declaration of SFML classes
namespace sf
{
    class Texture;
    class Font;
}

namespace Textures
{
    enum ID
    {
        Eagle,
        Raptor,
        Desert,
    };
}

// I don't understand why it is here
namespace Fonts
{
    enum ID
    {
        Main,
    };
}

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

using TextureHolder = ResourceHolder<sf::Texture, Textures::ID>;
using FontHolder = ResourceHolder<sf::Font, Fonts::ID>;

#endif //DAWUDENGINE_RESOURCEINDENTIFIERS_H
