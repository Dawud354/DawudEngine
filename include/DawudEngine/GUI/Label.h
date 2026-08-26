//
// Created by dawud on 8/24/26.
//

#ifndef DAWUDENGINE_LABEL_H
#define DAWUDENGINE_LABEL_H

#include <SFML/Graphics/Text.hpp>

#include "Component.h"
#include "ResourceIndentifiers.h"
#include "ResourceHolder.h"

namespace GUI {
    class Label : public Component {
    public:
        using SharedPtr =  std::shared_ptr<Label>;

        Label(const std::string& text, const FontHolder &fonts);

        bool isSelectable() const override;
        void setText(const std::string&  newText);

        void handleEvent(const sf::Event &event) override;

    private:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

        sf::Text text;
    };
}

#endif //DAWUDENGINE_LABEL_H
