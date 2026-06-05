//
// Created by dawud on 6/5/26.
//

#include "Entity.h"

void Entity::setVelocity(const sf::Vector2f& newVelocity) {
    velocity = newVelocity;
}

void Entity::setVelocity(float vx, float vy)
{
    velocity.x = vx;
    velocity.y = vy;
}

sf::Vector2f Entity::getVelocity() const
{
    return velocity;
}

void Entity::updateCurrent(sf::Time dt)
{
    move(velocity * dt.asSeconds());
}