//
// Created by dawud on 6/5/26.
//

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <cmath>
#include <memory>

#include "DataTables.h"
#include "ResourceHolder.h"
#include "Utility.h"
#include "Aircraft.h"
#include "Command.h"
#include "Pickup.h"
#include "Projectile.h"


// creates like a local private variable that only this file can access
namespace {
    const std::vector<AircraftData> Table = initialiseAircraftData();

    // i guess now i know how to make local helper functions that are hidden
    // idk how much this helps but at least know i don't have to remember how to write static cast properly
    int TypeToInt(Aircraft::Type type) {
        return static_cast<int>(type);
    }
}


Aircraft::Aircraft(Type type, const TextureHolder& textures, const FontHolder& fonts)
: Entity(Table[TypeToInt(type)].hitpoints)
, type(type)
, sprite(textures.get(Table[TypeToInt(type)].texture))
, fireCommand()
, missileCommand()
, fireCountdown(sf::Time::Zero)
, isFiring(false)
, mIsMarkedForRemoval(false)
, fireRateLevel(1)
, spreadLevel(1)
, missileAmmo(2)
, dropPickupCommand()
, travelledDistance(0.f)
, directionIndex(0)
, healthDisplay(nullptr)
, missileDisplay(nullptr)
{
    centerOrigin(sprite);

    fireCommand.category = Category::SceneAirLayer;
    fireCommand.action = [this, &textures] (SceneNode& node, sf::Time) {
        createBullets(node, textures);
    };

    missileCommand.category = Category::SceneAirLayer;
    missileCommand.action = [this, &textures] (SceneNode& node, sf::Time) {
        createProjectile(node, Projectile::Type::Missile,0.f, 0.5f,  textures);
    };

    std::unique_ptr<TextNode> tempHealthDisplay(new TextNode(fonts, ""));
    // have a pointer so we can get the text node
    healthDisplay = tempHealthDisplay.get();
    attachChild(std::move(tempHealthDisplay));

    if (getCategory() == Category::PlayerAircraft) {
        std::unique_ptr<TextNode> tempMissileDisplay(new TextNode(fonts, ""));
        tempMissileDisplay->setPosition(0,70);
        missileDisplay = tempMissileDisplay.get();
        attachChild(std::move(tempMissileDisplay));
    }

    updateTexts();
}

void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}

void Aircraft::updateCurrent(sf::Time dt, CommandQueue& commands) {
    // An entity has been destroyed, check for a pickup drop and mark for removal
    if (isDestroyed()) {
        checkPickupDrop(commands);

        mIsMarkedForRemoval = true;
        return;
    }

    // check if bullet or missile fired
    checkProjectileLaunch(dt, commands);

    //update enemy movement pattern
    updateMovementPattern(dt);
    // do this to prevent a loop (well I think so)
    Entity::updateCurrent(dt, commands);

    // update texts
    updateTexts();
}

unsigned int Aircraft::getCategory() const
{
    if (isAllied())
        return Category::PlayerAircraft;
    else
        return Category::EnemyAircraft;
}

sf::FloatRect Aircraft::getBoundingRect() const {
    return getWorldTransform().transformRect(sprite.getGlobalBounds());
}

bool Aircraft::isMarkedForRemoval() const
{
    return mIsMarkedForRemoval;
}

bool Aircraft::isAllied() const
{
    return type == Type::Eagle;
}

float Aircraft::getMaxSpeed() const
{
    return Table[TypeToInt(type)].speed;
}

void Aircraft::increaseFireRate() {
    if (fireRateLevel < 10)
        // I learnt that this is a preincrement
        // this is better cos it creates no copies so it faster
        ++fireRateLevel;
}

void Aircraft::increaseSpread() {
    if (spreadLevel <3)
        ++spreadLevel;
}

void Aircraft::collectMissiles(unsigned int count)
{
	missileAmmo += count;
}

void Aircraft::fire() {
    // only ships with fire interval != 0 can fire
    if (Table[TypeToInt(type)].fireInterval != sf::Time::Zero)
        isFiring = true;
}

void Aircraft::launchMissie() {
    if (missileAmmo > 0) {
        isLaunchingMissile = true;
        --missileAmmo;
    }
}

void Aircraft::updateMovementPattern(sf::Time dt) {
    // Enemy airplane movement pattern. not for player
    const std::vector<Direction>& directions = Table[TypeToInt(type)].directions;
    if (!directions.empty()) {
        // change direction if we have moved long enough in current one
        if (travelledDistance > directions[directionIndex].distance) {
            // The % allows me to loop back
            directionIndex = (directionIndex + 1) % directions.size();
            travelledDistance = 0;
        }

        // compute velocity from direction
        float radians = toRadian(directions[directionIndex].angle + 90.f);
        float vx = getMaxSpeed() * std::cos(radians);
        float vy = getMaxSpeed() * std::sin(radians);

        setVelocity(vx, vy);

        travelledDistance += getMaxSpeed() + dt.asSeconds();
    }
}

void Aircraft::checkPickupDrop(CommandQueue &commands) {
    if (!isAllied() && randomInt(3) == 0)
        commands.push(dropPickupCommand);
}

void Aircraft::checkProjectileLaunch( sf::Time dt, CommandQueue &commands) {
    // enemies fire all the time
    if (!isAllied())
        fire();

    // check for automatic gunfire. allow in intervals
    if (isFiring && fireCountdown <= sf::Time::Zero) {
        // interval expired so we can fire
        commands.push(fireCommand);
        fireCountdown += Table[TypeToInt(type)].fireInterval / (fireRateLevel + 1.f);
        isFiring = false;
    } else if (fireCountdown > sf::Time::Zero) {
        // interval not expired so increase it
        fireCountdown -= dt;
        isFiring = false;
    }

    // check for missile launch
    if (isLaunchingMissile) {
        commands.push(missileCommand);
        isLaunchingMissile = false;
    }
}

void Aircraft::createBullets(SceneNode& node, const TextureHolder& textures) const {
    // ? is like a shorthand if else. follows pattern:
    // condition ? value if true: value if false
    Projectile::Type type = isAllied() ? Projectile::Type::AlliedBullet : Projectile::Type::EnemyBullet;

    switch (spreadLevel) {
        case 1:
            createProjectile(node, type, 0.0f, 0.5f, textures);
            break;
        case 2:
            createProjectile(node, type, -0.33f, 0.33f, textures);
            createProjectile(node, type, +0.33f, 0.33f, textures);
            break;
        case 3:
            createProjectile(node, type, -0.5f, 0.33f, textures);
            createProjectile(node, type,  0.0f, 0.5f, textures);
            createProjectile(node, type, +0.5f, 0.33f, textures);
            break;
    }
}

void Aircraft::createProjectile(SceneNode &node, Projectile::Type type, float xOffset, float yOffset, const TextureHolder &textures) const {
    std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(type, textures);

    sf::Vector2f offset(xOffset * sprite.getGlobalBounds().width, yOffset * sprite.getGlobalBounds().height);
    sf::Vector2f velocity(0, projectile->getMaxSpeed());

    // sign is used cos enemies are flipped in relation to the player
    const float sign =  isAllied() ? -1.f : 1.f;
    projectile->setPosition(getWorldPosition() + offset * sign);
    projectile->setVelocity(velocity * sign);
    node.attachChild(std::move(projectile));
}

void Aircraft::createPickup(SceneNode &node, const TextureHolder &textures) const {
    // breaking this into 2 lines made it easier to read
    int randomIndex = randomInt(static_cast<int>(Pickup::Type::TypeCount));
    auto tempType = static_cast<Pickup::Type>(randomIndex);

    std::unique_ptr<Pickup> pickup = std::make_unique<Pickup>(tempType, textures);
    pickup->setPosition(getWorldPosition());
    pickup->setVelocity(0.f, 1.f);
    node.attachChild(std::move(pickup));
}

void Aircraft::updateTexts() {
    healthDisplay->setString(std::to_string(getHitpoints()) + " HP");
    healthDisplay->setPosition(0.f, 50.f);
    healthDisplay->setRotation(-getRotation());

    if (missileDisplay) {
        if (missileAmmo == 0)
            missileDisplay->setString("M: 0");
        else
            missileDisplay->setString("M: " + std::to_string(missileAmmo));
    }
}
