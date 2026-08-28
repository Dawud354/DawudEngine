//
// Created by dawud on 6/5/26.
//

#include "World.h"
#include "Projectile.h"
#include "Pickup.h"
#include "TextNode.h"
#include "SpriteNode.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <algorithm>
#include <cmath>
#include <limits>
#include <memory>

// I put the function here so it is local
// the book didn't and had it lying around
namespace {
    bool matchesCategories(SceneNode::Pair &colliders, Category::Type type1, Category::Type type2) {
        unsigned int category1 = colliders.first->getCategory();
        unsigned int category2 = colliders.second->getCategory();

        // Make sure first pair entry has category type1 and second has type2
        if (type1 & category1 && type2 & category2) {
            return true;
        } else if (type1 & category2 && type2 & category1) {
            std::swap(colliders.first, colliders.second);
            return true;
        } else {
            return false;
        }
    }
}

World::World(sf::RenderWindow &window, FontHolder &fonts)
    : window(window)
      , worldView(window.getDefaultView())
      , fonts(fonts)
      , textures()
      , sceneGraph()
      , sceneLayers()
      , worldBounds(0.f, 0.f, worldView.getSize().x, 2000.f)
      , spawnPosition(worldView.getSize().x / 2.f, worldBounds.height - worldView.getSize().y / 2.f)
      , scrollSpeed(-50.f)
      , playerAircraft(nullptr)
      , enemySpawnPoints()
      , activeEnemies() {
    loadTextures();
    buildScene();

    // Prepare the view
    worldView.setCenter(spawnPosition);
}

void World::update(sf::Time dt) {
    // Scroll the world
    worldView.move(0.f, scrollSpeed * dt.asSeconds());
    // reset player velocity
    playerAircraft->setVelocity(0.f, 0.f);

    // set up commands to destroy entities and guide missiles
    destroyEntitiesOutsideView();
    guideMissiles();

    // forward commands to the scene graph
    while (commandQueue.isEmpty())
        sceneGraph.onCommand(commandQueue.pop(), dt);

    // adapt velocity (scrolling, diagonal correction)
    adaptPlayerVelocity();

    // collision detection
    handleCollisions();

    // remove all destroyed entities and make new ones
    sceneGraph.removeWrecks();
    spawnEnemies();

    // normal update step and adapt position
    sceneGraph.update(dt, commandQueue);
    adaptPlayerPosition();
}

void World::draw() {
    window.setView(worldView);
    window.draw(sceneGraph);
}

CommandQueue &World::getCommandQueue() {
    return commandQueue;
}

bool World::hasAlivePlayer() const {
    return !playerAircraft->isMarkedForRemoval();
}

bool World::hasPlayerReachedEnd() const {
    return !worldBounds.contains(playerAircraft->getPosition());
}

void World::loadTextures() {
    textures.load(Textures::Eagle, "Media/Textures/Eagle.png");
    textures.load(Textures::Raptor, "Media/Textures/Raptor.png");
    textures.load(Textures::Raptor, "Media/Textures/Avenger.png");
    textures.load(Textures::Desert, "Media/Textures/Desert.png");

    textures.load(Textures::Raptor, "Media/Textures/Bullet.png");
    textures.load(Textures::Raptor, "Media/Textures/Missile.png");

    textures.load(Textures::Raptor, "Media/Textures/HealthRefill.png");
    textures.load(Textures::Raptor, "Media/Textures/MissileRefill.png");
    textures.load(Textures::Raptor, "Media/Textures/FireSpread.png");
    textures.load(Textures::Raptor, "Media/Textures/FireRate.png");
}

void World::adaptPlayerPosition() {
    // Keep players position inside the screen bounds. Keep borderDistance from edge
    sf::FloatRect viewBounds = getViewBounds();
    const float borderDistance = 40.f;

    sf::Vector2f position = playerAircraft->getPosition();
    position.x = std::max(position.x, viewBounds.left + borderDistance);
    position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
    position.y = std::max(position.y, viewBounds.top + borderDistance);
    position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);
    playerAircraft->setPosition(position);
}

void World::adaptPlayerVelocity() {
    sf::Vector2f velocity = playerAircraft->getVelocity();

    // if moving diagonally, reduce velocity
    if (velocity.x != 0.f && velocity.y != 0.f)
        playerAircraft->setVelocity(velocity / std::sqrt(2.f));

    // add scrolling velocity
    playerAircraft->accelerate(0.f, scrollSpeed);
}

void World::handleCollisions() {
    std::set<SceneNode::Pair> collisionPairs;
    sceneGraph.checkSceneCollision(sceneGraph, collisionPairs);

    for (auto pair: collisionPairs) {
        if (matchesCategories(pair, Category::PlayerAircraft, Category::EnemyAircraft)) {
            auto &player = static_cast<Aircraft &>(*pair.first);
            auto &enemy = static_cast<Aircraft &>(*pair.second);

            // collision so player takes damage = enemy remaining hp
            player.damage((enemy.getHitpoints()));
            enemy.destroy();
        } else if (matchesCategories(pair, Category::PlayerAircraft, Category::Pickup)) {
            auto &player = static_cast<Aircraft &>(*pair.first);
            auto &pickup = static_cast<Pickup &>(*pair.second);

            // apply pickup
            pickup.apply(player);
            pickup.destroy();
        } else if (matchesCategories(pair, Category::EnemyAircraft, Category::AlliedAircraft)
                   || matchesCategories(pair, Category::PlayerAircraft, Category::EnemyAircraft)) {
            auto &aircraft = static_cast<Aircraft &>(*pair.first);
            auto &projectile = static_cast<Projectile &>(*pair.second);

            // apply projectile damage and destroy projectile
            aircraft.damage(projectile.getDamage());
            projectile.destroy();
        }
    }
}

void World::buildScene() {
    // Initialize the different layers
    for (std::size_t i = 0; i < static_cast<int>(Layer::LayerCount); ++i) {
        Category::Type category = (i == static_cast<int>(Layer::Air)) ? Category::SceneAirLayer : Category::None;

        SceneNode::UniquePtr layer = std::make_unique<SceneNode>(category);
        sceneLayers[i] = layer.get();

        sceneGraph.attachChild(std::move(layer));
    }

    // Prepare the tiled background
    sf::Texture &texture = textures.get(Textures::Desert);
    sf::IntRect textureRect(worldBounds);
    texture.setRepeated(true);

    // Add the background sprite to the scene
    std::unique_ptr<SpriteNode> backgroundSprite = std::make_unique<SpriteNode>(texture, textureRect);
    backgroundSprite->setPosition(worldBounds.left, worldBounds.top);
    sceneLayers[static_cast<int>(Layer::Background)]->attachChild(std::move(backgroundSprite));

    // Add player's aircraft
    std::unique_ptr<Aircraft> player = std::make_unique<Aircraft>(Aircraft::Type::Eagle, textures, fonts);
    playerAircraft = player.get();
    playerAircraft->setPosition(spawnPosition);
    playerAircraft->setVelocity(40.f, scrollSpeed);
    sceneLayers[static_cast<int>(Layer::Air)]->attachChild(std::move(player));

    addEnemies();
}

void World::addEnemies() {
    // Add enemies to the spawn point container
    addEnemy(Aircraft::Type::Raptor, 0.f, 500.f);
    addEnemy(Aircraft::Type::Raptor, 0.f, 1000.f);
    addEnemy(Aircraft::Type::Raptor, +100.f, 1100.f);
    addEnemy(Aircraft::Type::Raptor, -100.f, 1100.f);
    addEnemy(Aircraft::Type::Avenger, -70.f, 1400.f);
    addEnemy(Aircraft::Type::Avenger, -70.f, 1600.f);
    addEnemy(Aircraft::Type::Avenger, 70.f, 1400.f);
    addEnemy(Aircraft::Type::Avenger, 70.f, 1600.f);

    // Sort all enemies according to their y value, such that lower enemies are checked first for spawning
    std::sort(enemySpawnPoints.begin(), enemySpawnPoints.end(), [](SpawnPoint lhs, SpawnPoint rhs) {
        return lhs.y < rhs.y;
    });
}

void World::addEnemy(Aircraft::Type type, float relX, float relY) {
    SpawnPoint spawn(type, spawnPosition.x + relX, spawnPosition.y - relY);
    enemySpawnPoints.emplace_back(spawn);
}

void World::spawnEnemies() {
    // spawn all enemies entering the view area
    while (!enemySpawnPoints.empty()
           && enemySpawnPoints.back().y > getBattlefieldBounds().top) {
        SpawnPoint spawn = enemySpawnPoints.back();

        std::unique_ptr<Aircraft> enemy = std::make_unique<Aircraft>(spawn.type, textures, fonts);
        enemy->setPosition(spawn.x, spawn.y);
        enemy->setRotation(180.f);

        sceneLayers[static_cast<int>(Layer::Air)]->attachChild(std::move(enemy));

        // Enemy is spawned, remove from the to spawn list
        enemySpawnPoints.pop_back();
    }
}

void World::destroyEntitiesOutsideView() {
    Command command;
    command.category = Category::Projectile | Category::EnemyAircraft;
    command.action = derivedAction<Entity>([this](Entity &e, sf::Time) {
        if (!getBattlefieldBounds().intersects(e.getBoundingRect()))
            e.destroy();
    });

    commandQueue.push(command);
}

void World::guideMissiles() {
    // make a command that stores all active enemies
    Command enemyCollector;
    enemyCollector.category = Category::EnemyAircraft;
    enemyCollector.action = derivedAction<Aircraft>([this](Aircraft &enemy, sf::Time) {
        if (!enemy.isDestroyed())
            activeEnemies.push_back(&enemy);
    });

    // setup command to guide all missiles to the enemt which is cloest to the player
    Command missileGuider;
    missileGuider.category = Category::AlliedProjectile;
    missileGuider.action = derivedAction<Projectile>([this](Projectile &missile, sf::Time) {
        // ignore normal missile
        if (!missile.isGuided())
            return;

        float minDistance = std::numeric_limits<float>::max();
        Aircraft *closestEnemy = nullptr;

        for (Aircraft *enemy: activeEnemies) {
            float enemyDistance = distance(missile, *enemy);

            if (enemyDistance < minDistance) {
                closestEnemy = enemy;
                minDistance = enemyDistance;
            }
        }

        if (closestEnemy)
            missile.guideTowards(closestEnemy->getWorldPosition());
    });


    // push commands and reset active enemies
    commandQueue.push(enemyCollector);
    commandQueue.push(missileGuider);
    activeEnemies.clear();
}

sf::FloatRect World::getViewBounds() const {
    return sf::FloatRect(worldView.getCenter() - worldView.getSize() / 2.f, worldView.getSize());
}

sf::FloatRect World::getBattlefieldBounds() const {
    // return view bounds + some area up top where enemies spawn
    sf::FloatRect bounds = getViewBounds();
    bounds.top -=100.f;
    bounds.height +=100.f;

    return bounds;
}
