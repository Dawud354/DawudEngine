//
// Created by dawud on 8/24/26.
//

#ifndef DAWUDENGINE_PICKUP_H
#define DAWUDENGINE_PICKUP_H

#include "Entity.h"
#include "ResourceIndentifiers.h"

#include <SFML/Graphics/Sprite.hpp>


class Aircraft;

class Pickup : public Entity {
public:
    enum class Type {
        HealthRefill,
        MissileRefill,
        FireSpread,
        FireRate,
        TypeCount
    };

    Pickup(Type type, const TextureHolder &textures);

    unsigned int getCategory() const override;
    sf::FloatRect getBoundingRect() const override;

    void apply(Aircraft &player) const;

protected:
    void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    Type type;
    sf::Sprite sprite;
};


#endif //DAWUDENGINE_PICKUP_H
