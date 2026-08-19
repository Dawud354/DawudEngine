//
// Created by dawud on 6/4/26.
//

#ifndef DAWUDENGINE_SCENENODE_H
#define DAWUDENGINE_SCENENODE_H
#include <memory>
#include <set>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Time.hpp>


#include <vector>

#include "Category.h"
#include "CommandQueue.h"

// forward declaration
struct Command;
/*
 * This class is used make our tree structure to store game stuff that is to be drawn
 * Often most of the stuff inside will be an entity.
 * The node can have an arbitrary amount of children
 */

class SceneNode:  public sf::Transformable , public sf::Drawable{
    public:

        // Delete the copy operator and constructor
        SceneNode(const SceneNode& other) = delete;
        SceneNode& operator=(const SceneNode& other) = delete;

        // The book originally used a typedef, but I learnt that using is the better new way to do it so I used that instead
        using UniquePtr = std::unique_ptr<SceneNode>;
        using Pair = std::pair<SceneNode*, SceneNode*>;

        explicit SceneNode(Category::Type category = Category::None);

        void attachChild(UniquePtr child);
        UniquePtr detachChild(const SceneNode& child);

        void update(sf::Time dt,  CommandQueue& commands);

        sf::Vector2f getWorldPosition() const;
        sf::Transform getWorldTransform() const;

        virtual unsigned int getCategory() const;
        void onCommand(const Command& command, sf::Time dt);

        void checkSceneCollision(SceneNode& sceneGraph, std::set<Pair>& collisionPairs);
        void checkNodeCollision(SceneNode& node, std::set<Pair>& collisionPairs);
        void removeWrecks();
        virtual sf::FloatRect getBoundingRect() const;
        virtual bool isMarkedForRemoval() const;
        virtual bool isDestroyed() const;



    private:

        virtual void updateCurrent(sf::Time dt,CommandQueue& commands);
        void updateChildren(sf::Time dt, CommandQueue& commands);
        // book made this private and override
        // I am not sure as to why though. the explanation was very complex
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        void drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;
        // used for debugging purposes
        void drawBoundingRect(sf::RenderTarget& target, sf::RenderStates states) const;

        std::vector<UniquePtr> children;
        // used to traverse up the graph
        // fine to be a raw pointer as the way our code is it would be very hard
        // to have a dangling pointer
        SceneNode* parent;
        Category::Type defaultCategory;


};

bool collision(const SceneNode& node1, const SceneNode& node2);
float distance(const SceneNode& node1, const SceneNode& node2);

#endif //DAWUDENGINE_SCENENODE_H
