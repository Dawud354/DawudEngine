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
    explicit World(sf::RenderWindow& window);
    void update(sf::Time dt);
    void draw();
    CommandQueue& getCommandQueue();


private:
    void loadTextures();
    void buildScene();

    // TODO: Change this to an enum class
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
    CommandQueue mCommandQueue;

    sf::FloatRect mWorldBounds;
    sf::Vector2f mSpawnPosition;
    float mScrollSpeed;
    Aircraft* mPlayerAircraft;
};


#endif //DAWUDENGINE_WORLD_H
