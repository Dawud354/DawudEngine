//
// Created by dawud on 6/5/26.
//

#ifndef DAWUDENGINE_WORLD_H
#define DAWUDENGINE_WORLD_H

#include "Aircraft.h"
#include "SceneNode.h"
#include "ResourceHolder.h"
#include "ResourceIndentifiers.h"

#include <SFML/Graphics/View.hpp>


#include <array>
#include <SFML/System/Time.hpp>

#include "CommandQueue.h"


// Forward declaration
// Book did it to make the class more lightweight
namespace sf
{
    class RenderWindow;
}

class World {
public:
    explicit World(sf::RenderWindow& window, FontHolder& fonts);
    void update(sf::Time dt);
    void draw();
    // delete copy constructor
    World(const World& other) = delete;
    World& operator=(const World& other) = delete;

    CommandQueue& getCommandQueue();

    bool hasAlivePlayer() const;
    bool hasPlayerReachedEnd() const;

private:
    void loadTextures();
    void adaptPlayerPosition();
    void adaptPlayerVelocity();
    void handleCollisions();

    void buildScene();
    void addEnemies();
    void addEnemy(Aircraft::Type type, float relX, float relY);
    void spawnEnemies();
    void destroyEntitiesOutsideView();
    void guideMissiles();
    sf::FloatRect getViewBounds() const;
    sf::FloatRect getBattlefieldBounds() const;

    enum class Layer
    {
        Background,
        Air,
        LayerCount
    };

    struct SpawnPoint
    {
        SpawnPoint(Aircraft::Type type, float x, float y)
        : type(type)
        , x(x)
        , y(y)
        {
        }

        Aircraft::Type type;
        float x;
        float y;
    };

    sf::RenderWindow& window;
    sf::View worldView;
    TextureHolder textures;
    FontHolder& fonts;

    SceneNode sceneGraph;
    std::array<SceneNode*, static_cast<int>(Layer::LayerCount)> sceneLayers;
    CommandQueue commandQueue;

    sf::FloatRect worldBounds;
    sf::Vector2f spawnPosition;
    float scrollSpeed;
    Aircraft* playerAircraft;

    std::vector<SpawnPoint> spawnPoints;
    std::vector<Aircraft*> activeEnemies;
};


#endif //DAWUDENGINE_WORLD_H
