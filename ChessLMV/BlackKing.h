#pragma once

#include <SDL.h>

#include "GameObjectInsertion.h"
#include "GameWindow.h"
#include "HelpFunctions.hpp"

// ----------------------------------------------------------------------------
class BlackKing : public GameObjectInsertion
{
    public:
        BlackKing( GameWindow *inputGameWindow, IntPoint position );
        BlackKing( GameWindow *inputGameWindow );
        ~BlackKing();
};



// ----------------------------------------------------------------------------