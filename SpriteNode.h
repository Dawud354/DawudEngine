//
// Created by dawud on 6/5/26.
//

#ifndef DAWUDENGINE_SPRITENODE_H
#define DAWUDENGINE_SPRITENODE_H

#include "SceneNode.h"
#include <SFML/Graphics/Sprite.hpp>

/*
 * The explicit keyword stops implicit conversions
 * An implicit convertion is when we can do: SpriteNode node = (a texture object)
 * The compiler will implicitly convert this texture into a sprite node
 * I do not want this so we like remove this feature by writing explicit
*/

class SpriteNode : public SceneNode{
public:
    explicit SpriteNode(const sf::Texture& texture);
    SpriteNode(const sf::Texture& texture, const sf::IntRect& textureRect);


private:
    // I need to remember to avoid using virtual methods as it is an old c++ thing
    // I should be using overr
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Sprite mSprite;
};


#endif //DAWUDENGINE_SPRITENODE_H
