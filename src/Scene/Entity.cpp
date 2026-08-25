//
// Created by dawud on 6/5/26.
//

#include <cassert>

#include "Entity.h"

Entity::Entity(int hitpoints)
    :velocity()
    , hp(hitpoints) {

}

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

void Entity::accelerate(sf::Vector2f acceleration)
{
    velocity += acceleration;
}

void Entity::accelerate(float vx, float vy)
{
    velocity.x += vx;
    velocity.y += vy;
}

int Entity::getHitpoints() const {
    return hp;
}

void Entity::repair(int points) {
    assert(points > 0);

    hp += points;
}

void Entity::damage(int points) {
    assert(points > 0);

    hp -= points;
}

void Entity::destroy() {
    hp = 0;
}

bool Entity::isDestroyed() const {
    return hp <= 0;
}

void Entity::updateCurrent(sf::Time dt, CommandQueue &commands) {
    move(velocity * dt.asSeconds());
}
