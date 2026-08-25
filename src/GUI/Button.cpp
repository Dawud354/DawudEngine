//
// Created by dawud on 8/23/26.
//

#include "GUI/Button.h"

#include <SFML/Graphics/RenderTarget.hpp>

#include "ResourceHolder.h"
#include "Utility.h"

namespace GUI {

    Button::Button(const FontHolder& fonts, const TextureHolder& textures)
    : callback()
    , normalTexture(textures.get(Textures::ButtonNormal))
    , selectedTexture(textures.get(Textures::ButtonSelected))
    , pressedTexture(textures.get(Textures::ButtonPressed))
    , sprite()
    , text("", fonts.get(Fonts::Main), 16)
    , isToggle(false) {
        sprite.setTexture(normalTexture);

        sf::FloatRect bounds = sprite.getLocalBounds();
        text.setPosition(bounds.width / 2.f, bounds.height / 2.f);
    }

    void Button::setCallback(Callback newCallback) {
        callback = std::move(newCallback);
    }

    void Button::setText(const std::string& newText) {
        text.setString(newText);
        centerOrigin(text);
    }

    void Button::setToggle(bool flag)
    {
        isToggle = flag;
    }

    bool Button::isSelectable() const
    {
        return true;
    }

    void Button::select()
    {
        Component::select();

        sprite.setTexture(selectedTexture);
    }

    void Button::deselect()
    {
        Component::deselect();

        sprite.setTexture(normalTexture);
    }

    void Button::activate() {
        Component::activate();

        // if we are toggle then we should show that the button is pressed
        if (isToggle) {
            sprite.setTexture(pressedTexture);
        }

        if (callback) {
            callback();
        }

        // if we are not toggle then deactivate the button
        if (!isToggle) {
            deactivate();
        }
    }

    void Button::deactivate() {
        Component::deactivate();

        if (isToggle) {
            // reset texture to right one depending on if we are selected or not
            if (isSelected())
                sprite.setTexture(selectedTexture);
            else
                sprite.setTexture(normalTexture);
        }
    }

    // idk why this is empty but the book has it like this
    void Button::handleEvent(const sf::Event &event) {

    }

    void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const {
        states.transform *= getTransform();
        target.draw(sprite, states);
        target.draw(text, states);
    }
}
