//
// Created by dawud on 6/5/26.
//

#ifndef DAWUDENGINE_ENTITY_H
#define DAWUDENGINE_ENTITY_H

#include "SceneNode.h"

class Entity : public SceneNode
{
public:
    void setVelocity(const sf::Vector2f& newVelocity);
    void setVelocity(float vx, float vy);
    sf::Vector2f getVelocity() const;
    void accelerate(sf::Vector2f acceleration);
    void accelerate(float vx, float vy);


private:
    void updateCurrent(sf::Time dt) override;

    // The SFML book made every entity have a velocity. It was just a design choice
    sf::Vector2f velocity;
};


#endif //DAWUDENGINE_ENTITY_H
