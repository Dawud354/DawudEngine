//
// Created by dawud on 8/24/26.
//

#include "GUI/Container.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

namespace GUI {
    Container::Container()
        : children(),
          selectedChild(-1) {
    }

    void Container::pack(const Component::SharedPtr& component) {
        children.push_back(component);

        if (!hasSelection() && component->isSelectable())
            select(children.size() - 1);
    }

    bool Container::isSelectable() const {
        return false;
    }

    void Container::handleEvent(const sf::Event &event) {
        // If we have selected a child then we give it the event
        if (hasSelection() && children[selectedChild]->isActive()) {
            children[selectedChild]->handleEvent(event);
        } else if (event.type == sf::Event::KeyReleased) {
            if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up) {
                selectPrevious();
            } else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down) {
                selectNext();
            } else if (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Space) {
                if (hasSelection()) {
                    children[selectedChild] -> activate();
                }
            }
        }
    }

    void Container::draw(sf::RenderTarget &target, sf::RenderStates states) const {
        states.transform *= getTransform();

        for (auto& child : children) {
            target.draw(*child, states);
        }
    }

    bool Container::hasSelection() const {
        return selectedChild >= 0;
    }

    void Container::select(std::size_t index) {
        if (children[index]->isSelectable()) {
            // deselect child if it has been selected
            if (hasSelection()) {
                children[selectedChild]->deselect();
            }

            children[index]->select();
            selectedChild = index;
        }
    }

    void Container::selectNext() {
        if (!hasSelection()) {
            return;
        }

        // search next component that is selectable and wrap around if needed
        int next = selectedChild;
        do
            next = (next + 1) % children.size();
        while (!children[next]->isSelectable());

        // select the component
        select(next);
    }

    void Container::selectPrevious() {
        // similar to selectNext
        if (!hasSelection()) {
            return;
        }

        // search next component that is selectable and wrap around if needed
        int prev = selectedChild;
        do
            prev = (prev + children.size() - 1) % children.size();
        while (!children[prev]->isSelectable());

        // select the component
        select(prev);
    }
}
