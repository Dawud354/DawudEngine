//
// Created by dawud on 6/12/26.
//

#ifndef DAWUDENGINE_COMMANDQUEUE_H
#define DAWUDENGINE_COMMANDQUEUE_H

#include "Command.h"

#include <queue>


// A thin wrapper class
// The class acts as a bridge between input and game logi
// The methods just call the underlying C++ Queue
class CommandQueue
{
public:
    void						push(const Command& command);
    Command						pop();
    bool						isEmpty() const;


private:
    std::queue<Command>			mQueue;
};


#endif //DAWUDENGINE_COMMANDQUEUE_H
