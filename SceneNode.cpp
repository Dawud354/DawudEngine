//
// Created by dawud on 6/4/26.
//

#include "SceneNode.h"

#include <cassert>

SceneNode::SceneNode() : children(), parent(nullptr) {}

void SceneNode::attachChild(UniquePtr child) {
    child->parent = this;
    children.push_back(std::move(child));
}

SceneNode::UniquePtr SceneNode::detachChild(const SceneNode &child) {
    // i think there is a better solution but the SFML book uses this Lambda way
    auto found = std::find_if(children.begin(), children.end(),
        [&] (UniquePtr& p) {return p.get() == &child;}
    );
    assert(found != children.end());

    UniquePtr result = std::move(*found);
    result ->parent = nullptr;
    children.erase(found);
    return result;

}

void SceneNode::update(sf::Time dt)
{
    updateCurrent(dt);
    updateChildren(dt);
}

void SceneNode::updateCurrent(sf::Time)
{
    // Do nothing by default
}

void SceneNode::updateChildren(sf::Time dt)
{
    // in this case using {} just is not worth it
    for (const UniquePtr& child : children)
        child->update(dt);
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // Apply transform of current node
    states.transform *= getTransform();

    // Draw node and children with changed transform
    drawCurrent(target, states);
    drawChildren(target, states);
}

void SceneNode::drawCurrent(sf::RenderTarget&, sf::RenderStates) const
{
    // Do nothing by default
}

void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (const UniquePtr& child : children)
        child->draw(target, states);
}

sf::Vector2f SceneNode::getWorldPosition() const
{
    return getWorldTransform() * sf::Vector2f();
}

sf::Transform SceneNode::getWorldTransform() const
{
    sf::Transform transform = sf::Transform::Identity;

    for (const SceneNode* node = this; node != nullptr; node = node->parent)
        transform = node->getTransform() * transform;

    return transform;
}