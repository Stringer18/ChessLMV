#pragma once

#include <SDL.h>

#include "GameObjectInsertion.h"
#include "GameWindow.h"
#include "HelpFunctions.hpp"

// ----------------------------------------------------------------------------
class WhiteKing : public GameObjectInsertion
{
    public:
        WhiteKing( GameWindow *inputGameWindow, IntPoint position );
        WhiteKing( GameWindow *inputGameWindow );
        ~WhiteKing();
};



// ----------------------------------------------------------------------------