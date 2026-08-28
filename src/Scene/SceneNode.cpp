//
// Created by dawud on 6/4/26.
//

#include "SceneNode.h"
#include "Category.h"
#include  "Utility.h"
#include "Command.h"


#include <cassert>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>



/*
 * Code is copied from SFML book
 */

SceneNode::SceneNode(Category::Type category)
    : children()
      , parent(nullptr)
      , defaultCategory(category) {
}

void SceneNode::attachChild(UniquePtr child) {
    child->parent = this;
    children.push_back(std::move(child));
}

SceneNode::UniquePtr SceneNode::detachChild(const SceneNode &child) {
    // I think there is a better solution but the SFML book uses this Lambda way
    auto found = std::find_if(children.begin(), children.end(),
                              [&](UniquePtr &p) { return p.get() == &child; }
    );
    assert(found != children.end());

    UniquePtr result = std::move(*found);
    result->parent = nullptr;
    children.erase(found);
    return result;
}

void SceneNode::update(sf::Time dt, CommandQueue& commands) {
    updateCurrent(dt,  commands);
    updateChildren(dt, commands);
}

void SceneNode::updateCurrent(sf::Time, CommandQueue&)
{
    // Do nothing by default
}

void SceneNode::updateChildren(sf::Time dt, CommandQueue& commands) {
    // in this case using {} just is not worth it
    for (const UniquePtr &child: children)
        child->update(dt, commands);
}

void SceneNode::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    // Apply transform of current node
    states.transform *= getTransform();

    // Draw node and children with changed transform
    drawCurrent(target, states);
    drawChildren(target, states);
}

void SceneNode::drawCurrent(sf::RenderTarget &, sf::RenderStates) const {
    // Do nothing by default
}

void SceneNode::drawChildren(sf::RenderTarget &target, sf::RenderStates states) const {
    for (const UniquePtr &child: children)
        child->draw(target, states);
}

void SceneNode::drawBoundingRect(sf::RenderTarget& target, sf::RenderStates) const {
    sf::FloatRect rect = getBoundingRect();

    sf::RectangleShape shape;
    shape.setPosition(sf::Vector2f(rect.left, rect.top));
    shape.setSize(sf::Vector2f(rect.width, rect.height));
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineColor(sf::Color::Red);
    shape.setOutlineThickness(1.f);

    target.draw(shape);
}

sf::Vector2f SceneNode::getWorldPosition() const {
    return getWorldTransform() * sf::Vector2f();
}

// This method goes through each parent until it gets to root
// It applied all the nodes transformations to get the world transformation
sf::Transform SceneNode::getWorldTransform() const {
    sf::Transform transform = sf::Transform::Identity;

    for (const SceneNode *node = this; node != nullptr; node = node->parent)
        transform = node->getTransform() * transform;

    return transform;
}

void SceneNode::onCommand(const Command& command, sf::Time dt) {
    // command the current node id the category matches
    if (command.category & getCategory())
        command.action(*this, dt);

    // command the children
    for (const UniquePtr &child: children)
        child->onCommand(command, dt);
}

unsigned int SceneNode::getCategory() const {
    return defaultCategory;
}

void SceneNode::checkSceneCollision(SceneNode &sceneGraph, std::set<Pair> &collisionPairs) {
    checkNodeCollision(sceneGraph, collisionPairs);

    // check children
    for (const UniquePtr &child: sceneGraph.children)
        checkSceneCollision(*child, collisionPairs);
}

void SceneNode::checkNodeCollision(SceneNode &node, std::set<Pair> &collisionPairs) {
    if (this != &node && collision(*this, node) && !isDestroyed() && !node.isDestroyed())
        collisionPairs.insert(std::minmax(this, &node));

    for (const UniquePtr &child: children)
        child->checkNodeCollision(node, collisionPairs);
}

void SceneNode::removeWrecks() {
    // remove all children which requested so
    const auto wreckfieldBegin  = std::remove_if(children.begin(), children.end(), std::mem_fn(&SceneNode::isMarkedForRemoval));
    children.erase(wreckfieldBegin, children.end());

    // call function for all remaining children
    std::for_each(children.begin(), children.end(), std::mem_fn(&SceneNode::removeWrecks));
}

sf::FloatRect SceneNode::getBoundingRect() const
{
    return sf::FloatRect();
}

bool SceneNode::isMarkedForRemoval() const
{
    // By default, remove node if entity is destroyed
    return isDestroyed();
}

bool SceneNode::isDestroyed() const
{
    // By default, scene node needn't be removed
    return false;
}

bool collision(const SceneNode &node1, const SceneNode &node2) {
    return node1.getBoundingRect().intersects(node2.getBoundingRect());
}

float distance(const SceneNode &node1, const SceneNode &node2) {
    return length(node1.getWorldPosition() - node2.getWorldPosition());
}

