//
// Created by dawud on 8/21/26.
//

#ifndef DAWUDENGINE_TEXTNODE_H
#define DAWUDENGINE_TEXTNODE_H
#include <SFML/Graphics/Text.hpp>

#include "ResourceIndentifiers.h"
#include "SceneNode.h"


class TextNode : public SceneNode
{
public:
    explicit TextNode(const FontHolder& fonts, const std::string& text);

    void setString(const std::string& newText);

protected:
    void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    sf::Text text;

};


#endif //DAWUDENGINE_TEXTNODE_H
