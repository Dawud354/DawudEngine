//
// Created by dawud on 8/24/26.
//

#ifndef DAWUDENGINE_CONTAINER_H
#define DAWUDENGINE_CONTAINER_H


#include <vector>
#include <memory>

#include "Component.h"

namespace GUI {
    class Container : public Component {
    public:
        using SharedPtr =  std::shared_ptr<Container>;

        Container();

        void pack(const Component::SharedPtr& component);

        bool isSelectable() const override;
        void handleEvent(const sf::Event &event) override;

    private:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

        bool hasSelection() const;
        void select(std::size_t index);
        void selectNext();
        void selectPrevious();

        std::vector<Component::SharedPtr> children;
        int selectedChild;
    };
}

#endif //DAWUDENGINE_CONTAINER_H
