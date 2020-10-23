#pragma once

#include <SDL.h>

#include "GameObjectInsertion.h"
#include "GameWindow.h"
#include "HelpFunctions.hpp"

// ----------------------------------------------------------------------------
class BlackQueen : public GameObjectInsertion
{
    public:
        BlackQueen( GameWindow *inputGameWindow, IntPoint position );
        BlackQueen( GameWindow *inputGameWindow );
        ~BlackQueen();
};



// ----------------------------------------------------------------------------