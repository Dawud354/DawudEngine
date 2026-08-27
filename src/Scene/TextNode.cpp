//
// Created by dawud on 8/21/26.
//

#include "TextNode.h"
#include "Utility.h"

#include <SFML/Graphics/RenderTarget.hpp>

#include "ResourceHolder.h"

TextNode::TextNode(const FontHolder &fonts, const std::string &text) {
    // I am being a bit lazy and using this instead of actually making the param name different
    this->text.setFont(fonts.get(Fonts::Main));
    this->text.setCharacterSize(20);
    setString(text);
}

void TextNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(text, states);
}

void TextNode::setString(const std::string &newText) {
    text.setString(newText);
    centerOrigin(text);
}
