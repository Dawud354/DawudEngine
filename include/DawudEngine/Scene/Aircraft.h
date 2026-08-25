//
// Created by dawud on 6/5/26.
//

#ifndef DAWUDENGINE_AIRCRAFT_H
#define DAWUDENGINE_AIRCRAFT_H

#include "Entity.h"
#include "Core/ResourceIndentifiers.h"
#include "Projectile.h"
#include "TextNode.h"

#include <SFML/Graphics/Sprite.hpp>


class Aircraft : public Entity
{
public:
    // i saw online to make count work i static cast
    // static_cast<int>(Example::Count)
    enum class Type
    {
        Eagle,
        Raptor,
        Avenger,
        TypeCount
    };


    Aircraft(Type type, const TextureHolder& textures,  const FontHolder& fonts);

    unsigned int getCategory() const override;
    sf::FloatRect getBoundingRect() const override;
    bool isMarkedForRemoval() const override;
    bool isAllied() const;
    float getMaxSpeed() const;

    void increaseFireRate();
    void increaseSpread();
    void collectMissiles(unsigned int count);

    void fire();
    void launchMissie();

// book for some reason had scene node have this private but then entity protected
// but in here it was back to private
// so i just left it as protected the whole time.
protected:
    void updateCurrent(sf::Time dt, CommandQueue &commands) override;


private:
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
    void updateMovementPattern(sf::Time dt);
    void checkPickupDrop(CommandQueue& commands);
    void checkProjectileLaunch(sf::Time dt, CommandQueue &commands);

    void createBullets(SceneNode& node, const TextureHolder& textures) const;
    void createProjectile(SceneNode& node, Projectile::Type type, float xOffset, float yOffset, const TextureHolder& textures) const;
    void createPickup(SceneNode& node, const TextureHolder& textures) const;

    void updateTexts();

    Type type;
    sf::Sprite sprite;
    Command fireCommand;
    Command missileCommand;
    sf::Time fireCountdown;
    bool isFiring;
    bool isLaunchingMissile;
    bool mIsMarkedForRemoval;

    int fireRateLevel;
    int spreadLevel;
    int missileAmmo;

    Command dropPickupCommand;
    float travelledDistance;
    std::size_t directionIndex;
    TextNode *healthDisplay;
    TextNode *missileDisplay;
};


#endif //DAWUDENGINE_AIRCRAFT_H
