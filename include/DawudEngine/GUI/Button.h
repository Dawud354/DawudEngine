//
// Created by dawud on 8/23/26.
//

#ifndef DAWUDENGINE_BUTTON_H
#define DAWUDENGINE_BUTTON_H

#include "Component.h"
#include "ResourceIndentifiers.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <string>
#include <memory>
#include <functional>

namespace GUI {
    class Button : public Component {
    public:
        using SharedPtr = std::shared_ptr<Button>;
        using Callback = std::function<void()>;

        Button(const FontHolder &fonts, const TextureHolder &textures);

        void setCallback(Callback callback);
        void setText(const std::string &text);
        void setToggle(bool flag);

        bool isSelectable() const override;
        void select() override;
        void deselect() override;

        void activate() override;
        void deactivate() override;

        void handleEvent(const sf::Event &event) override;

    private:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

        Callback callback;
        const sf::Texture &normalTexture;
        const sf::Texture &selectedTexture;
        const sf::Texture &pressedTexture;
        sf::Sprite sprite;
        sf::Text text;
        bool isToggle;
    };
}
#endif //DAWUDENGINE_BUTTON_H
