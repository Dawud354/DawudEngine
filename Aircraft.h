//
// Created by dawud on 6/5/26.
//

#ifndef DAWUDENGINE_AIRCRAFT_H
#define DAWUDENGINE_AIRCRAFT_H

#include "Entity.h"
#include "ResourceIndentifiers.h"
#include <SFML/Graphics/Sprite.hpp>


class Aircraft : public Entity
{
    public:
    enum Type
    {
        Eagle,
        Raptor,
    };


    public:
    Aircraft(Type type, const TextureHolder& textures);


    private:
    virtual void		drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;


    private:
    Type				type;
    sf::Sprite			sprite;
};


#endif //DAWUDENGINE_AIRCRAFT_H
