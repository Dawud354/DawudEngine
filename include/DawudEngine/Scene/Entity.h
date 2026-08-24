//
// Created by dawud on 6/5/26.
// Updated to chapter 7

#ifndef DAWUDENGINE_ENTITY_H
#define DAWUDENGINE_ENTITY_H

#include "SceneNode.h"
#include "CommandQueue.h"

class Entity : public SceneNode
{
public:
    explicit Entity(int hitpoints);

    void setVelocity(const sf::Vector2f& newVelocity);
    void setVelocity(float vx, float vy);
    sf::Vector2f getVelocity() const;
    void accelerate(sf::Vector2f acceleration);
    void accelerate(float vx, float vy);

    int getHitpoints() const;
    void repair(int points);
    void damage(int points);
    void destroy();
    bool isDestroyed() const override;

protected:
    void updateCurrent(sf::Time dt, CommandQueue& commands) override;


private:
    void updateCurrent(sf::Time dt);

    // The SFML book made every entity have a velocity. It was just a design choice
    sf::Vector2f velocity;
    int hp;
};


#endif //DAWUDENGINE_ENTITY_H
