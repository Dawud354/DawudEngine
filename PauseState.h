//
// Created by dawud on 6/26/26.
//

#ifndef DAWUDENGINE_PAUSESTATE_H
#define DAWUDENGINE_PAUSESTATE_H

#include "State.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class PauseState : public State
{
public:
    PauseState(StateStack& stack, Context context);

    virtual void		draw();
    virtual bool		update(sf::Time dt);
    virtual bool		handleEvent(const sf::Event& event);


private:
    sf::Sprite			mBackgroundSprite;
    sf::Text			mPausedText;
    sf::Text			mInstructionText;
};


#endif //DAWUDENGINE_PAUSESTATE_H
