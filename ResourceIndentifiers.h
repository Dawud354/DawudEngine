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

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

using TextureHolder = ResourceHolder<sf::Texture, Textures::ID>;

#endif //DAWUDENGINE_RESOURCEINDENTIFIERS_H
