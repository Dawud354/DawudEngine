//
// Created by dawud on 8/24/26.
//

#include "Pickup.h"
#include "DataTables.h"
#include "Category.h"
#include "ResourceHolder.h"
#include "Utility.h"

#include <SFML/Graphics/RenderTarget.hpp>

namespace
{
    const std::vector<PickupData> Table = initialisePickupData();
    // I have used this method a lot to convert enum class to int but idk if there is a better way
    int TypeToInt(Pickup::Type type) {
        return static_cast<int>(type);
    }
}

Pickup::Pickup(Type type, const TextureHolder &textures)
: Entity(1)
, type(type)
, sprite(textures.get(Table[TypeToInt(type)].texture))
{
    centerOrigin(sprite);
}

unsigned int Pickup::getCategory() const{
    return Category::Pickup;
}

sf::FloatRect Pickup::getBoundingRect() const {
    return getWorldTransform().transformRect(sprite.getGlobalBounds());
}

void Pickup::apply(Aircraft &player) const {
    Table[TypeToInt(type)].action(player);
}

void Pickup::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(sprite, states);
}
