//
// Created by dawud on 6/4/26.
//

#ifndef DAWUDENGINE_SCENENODE_H
#define DAWUDENGINE_SCENENODE_H
#include <memory>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Time.hpp>

#include <vector>

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

        SceneNode();
        void attachChild(UniquePtr child);
        UniquePtr detachChild(const SceneNode& child);

        void update(sf::Time dt);

        sf::Vector2f getWorldPosition() const;
        sf::Transform getWorldTransform() const;

    private:

        virtual void updateCurrent(sf::Time dt);
        void updateChildren(sf::Time dt);
        // book made this private and override
        // I am not sure as to why though. the explanation was very complex
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        void drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;


        std::vector<UniquePtr> children;
        // used to traverse up the graph
        // fine to be a raw pointer as the way our code is it would be very hard
        // to have a dangling pointer
        SceneNode* parent;


};


#endif //DAWUDENGINE_SCENENODE_H
