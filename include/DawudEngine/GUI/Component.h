//
// Created by dawud on 8/23/26.
//

#ifndef DAWUDENGINE_COMPONENT_H
#define DAWUDENGINE_COMPONENT_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include <memory>

// I was reading that the Google C++ guide did not like using forward deceleration cos it makes
// mistakes easier. But since the book did it like this I will stick  to this style.
namespace sf {
    class Event;
}

namespace GUI {
    class Component : public sf::Drawable, public sf::Transformable {
    public:
        // delete copy constructor
        Component(const Component &) = delete;
        Component &operator=(const Component &) = delete;

        using SharedPtr = std::shared_ptr<Component>;

        Component();
        virtual ~Component();

        virtual bool isSelectable() const = 0;
        bool isSelected() const;
        virtual void select();
        virtual void deselect();

        virtual bool isActive() const;
        virtual void activate();
        virtual void deactivate();

        virtual void handleEvent(const sf::Event &event) = 0;

    private:
        bool mIsSelected;
        bool mIsActive;
    };
}
#endif //DAWUDENGINE_COMPONENT_H
