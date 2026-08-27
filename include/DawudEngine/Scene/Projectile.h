//
// Created by dawud on 8/20/26.
//

#ifndef DAWUDENGINE_PROJECTILE_H
#define DAWUDENGINE_PROJECTILE_H
#include <SFML/Graphics/Sprite.hpp>

#include "Entity.h"
#include "ResourceIndentifiers.h"


class Projectile : public Entity
{
public:
    enum class Type
    {
        AlliedBullet,
        EnemyBullet,
        Missile,
        TypeCount
    };

    Projectile(Type type, const TextureHolder& textures);

    void guideTowards(sf::Vector2f);
    bool isGuided() const;

    unsigned int getCategory() const override;
    sf::FloatRect getBoundingRect() const override;
    float getMaxSpeed() const;
    int getDamage() const;

protected:
    void updateCurrent(sf::Time dt, CommandQueue &commands) override;


private:
    void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const override;


    Type type;
    sf::Sprite sprite;
    sf::Vector2f targetDirection;
};


#endif //DAWUDENGINE_PROJECTILE_H
