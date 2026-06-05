//
// Created by dawud on 6/5/26.
//

#ifndef DAWUDENGINE_WORLD_H
#define DAWUDENGINE_WORLD_H

#include "Aircraft.h"
#include "SceneNode.h"
#include "SpriteNode.h"
#include "ResourceHolder.h"
#include "ResourceIndentifiers.h"

#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


#include <array>
#include <SFML/System/Time.hpp>


// Forward declaration
namespace sf
{
    class RenderWindow;
}

class World {
public:
    explicit World(sf::RenderWindow& window);
    void update(sf::Time dt);
    void draw();


private:
    void loadTextures();
    void buildScene();

    enum Layer
    {
        Background,
        Air,
        LayerCount
    };


    sf::RenderWindow& mWindow;
    sf::View mWorldView;
    TextureHolder mTextures;

    SceneNode mSceneGraph;
    std::array<SceneNode*, LayerCount> mSceneLayers;

    sf::FloatRect mWorldBounds;
    sf::Vector2f mSpawnPosition;
    float mScrollSpeed;
    Aircraft* mPlayerAircraft;
};


#endif //DAWUDENGINE_WORLD_H
