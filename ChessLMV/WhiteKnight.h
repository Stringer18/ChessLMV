#pragma once

#include <SDL.h>

#include "GameObjectInsertion.h"
#include "GameWindow.h"
#include "HelpFunctions.hpp"

// ----------------------------------------------------------------------------
class WhiteKnight : public GameObjectInsertion
{
    public:
        WhiteKnight( GameWindow *inputGameWindow, IntPoint position );
        WhiteKnight( GameWindow *inputGameWindow );
        ~WhiteKnight();
};



// ----------------------------------------------------------------------------