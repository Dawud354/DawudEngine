//
// Created by dawud on 8/23/26.
//

// a cool class. it seems basic but it somehow can be so useful

#include "GUI/Component.h"

namespace GUI {
    Component::Component()
        : mIsSelected(false)
          , mIsActive(false) {
    }

    Component::~Component() = default;

    bool Component::isSelected() const {
        return mIsSelected;
    }

    void Component::select() {
        mIsSelected = true;
    }

    void Component::deselect() {
        mIsSelected = false;
    }

    bool Component::isActive() const {
        return mIsActive;
    }

    void Component::activate() {
        mIsActive = true;
    }

    void Component::deactivate() {
        mIsActive = false;
    }
}

}
