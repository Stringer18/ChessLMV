#pragma once

#include <SDL.h>

#include "GameObjectInsertion.h"
#include "GameWindow.h"
#include "HelpFunctions.hpp"

// ----------------------------------------------------------------------------
class BlackBishop : public GameObjectInsertion
{
    public:
        BlackBishop( GameWindow *inputGameWindow, IntPoint position );
        BlackBishop( GameWindow *inputGameWindow );
        ~BlackBishop();
};



// ----------------------------------------------------------------------------