//
// Created by dawud on 8/24/26.
//

#include "State/SettingsState.h"
#include "Utility.h"
#include "ResourceHolder.h"

#include <SFML/Graphics/RenderWindow.hpp>

SettingsState::SettingsState(StateStack &stack, Context context)
: State( stack, context )
, GUIContainer()
{
    backgroundSprite.setTexture(context.textures->get(Textures::TitleScreen));

    // build key binding button and labels
    addButtonLabel(PlayerInputHandler::Action::MoveLeft, 300.f, "Move Left", context);
    addButtonLabel(PlayerInputHandler::Action::MoveRight, 350.f, "Move Right", context);
    addButtonLabel(PlayerInputHandler::Action::MoveUp, 400.f, "Move Up", context);
    addButtonLabel(PlayerInputHandler::Action::MoveDown, 450.f, "Move Down", context);
    addButtonLabel(PlayerInputHandler::Action::Fire, 500.f, "Fire", context);
    addButtonLabel(PlayerInputHandler::Action::LaunchMissile, 550.f, "Missile", context);

    updateLabels();

    // make the back button
    auto backButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    backButton->setPosition(80.f, 620.f);
    backButton->setText("Back");
    backButton->setCallback(std::bind(&SettingsState::requestStackPop, this));

    GUIContainer.pack(backButton);
}

void SettingsState::draw() {
    sf::RenderWindow& window = *getContext().window;

    window.draw(backgroundSprite);
    window.draw(GUIContainer);
}

bool SettingsState::update(sf::Time)
{
    return true;
}

bool SettingsState::handleEvent(const sf::Event &event) {
    bool isKeyBinding = false;

    // iterate through all key binding buttons to see if they are being pressed
    // wait for the user to release the key
    // The book used normal enums so they didn't have to static cast
    for (int action = 0; action < static_cast<int>(Action::ActionCount); ++action) {
        if (bindingButtons[action]->isActive()) {
            isKeyBinding = true;
            if (event.type == sf::Event::KeyReleased) {
                getContext().player->assignKey(static_cast<PlayerInputHandler::Action>(action), event.key.code);
                bindingButtons[action]->deactivate();
            }
            break;
        }
    }

    // If pressed button changed key binding update labels. if not check other buttons
    if (isKeyBinding)
        updateLabels();
    else
        GUIContainer.handleEvent(event);
    return false;
}

void SettingsState::updateLabels() {
    PlayerInputHandler& player = *getContext().player;
    // bit weird i have to do two static casts but idk how else to loop over an enum
    for (int action = 0; action < static_cast<int>(Action::ActionCount); ++action) {
        sf::Keyboard::Key key = player.getAssignedKey(static_cast<PlayerInputHandler::Action>(action));
        bindingLabels[action]->setText(toString(key));
    }
}

void SettingsState::addButtonLabel(PlayerInputHandler::Action action, float y, const std::string &text, Context context) {
    int i = static_cast<int>(action);
    bindingButtons[i] = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    bindingButtons[i]->setPosition(80.f, y);
    bindingButtons[i]->setText(text);
    bindingButtons[i]->setToggle(true);

    bindingLabels[i] = std::make_shared<GUI::Label>("", *context.fonts);
    bindingLabels[i]->setPosition(300.f, y + 15.f);

    GUIContainer.pack(bindingButtons[i]);
    GUIContainer.pack(bindingLabels[i]);
}
