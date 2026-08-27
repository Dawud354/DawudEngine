//
// Created by dawud on 8/20/26.
//

#include "Projectile.h"
#include "DataTables.h"
#include "Utility.h"
#include "ResourceHolder.h"


#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <cmath>
#include <cassert>


namespace {
    const std::vector<ProjectileData> Table = initialiseProjectileData();

    int TypeToInt(Projectile::Type t) {
        return static_cast<int>(t);
    }
}

Projectile::Projectile(Type type, const TextureHolder &textures)
    : Entity(1)
      , type(type)
      , sprite(textures.get(Table[TypeToInt(type)].texture))
      , targetDirection() {
    centerOrigin(sprite);
}

void Projectile::guideTowards(sf::Vector2f position) {
    assert(isGuided());
    targetDirection = unitVector(position - getWorldPosition());
}

bool Projectile::isGuided() const {
    return type == Type::Missile;
}

void Projectile::updateCurrent(sf::Time dt, CommandQueue &commands) {
    if (isGuided()) {
        const float approachRate = 200.f;

        sf::Vector2f newVelocity = unitVector(approachRate * dt.asSeconds() * targetDirection + getVelocity());
        newVelocity *= getMaxSpeed();
        float angle = std::atan2(newVelocity.y, newVelocity.x);

        setRotation(toDegree(angle) + 90.f);
        setVelocity(newVelocity);
    }

    Entity::updateCurrent(dt, commands);
}

void Projectile::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}

unsigned int Projectile::getCategory() const {
    if (type == Type::EnemyBullet)
        return Category::EnemyProjectile;
    else
        return Category::AlliedProjectile;
}

sf::FloatRect Projectile::getBoundingRect() const {
    return getWorldTransform().transformRect(sprite.getGlobalBounds());
}

float Projectile::getMaxSpeed() const {
    return Table[TypeToInt(type)].speed;
}

int Projectile::getDamage() const {
    return Table[TypeToInt(type)].damage;
}
