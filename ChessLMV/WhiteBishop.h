#pragma once

#include <SDL.h>

#include "GameObjectInsertion.h"
#include "GameWindow.h"
#include "HelpFunctions.hpp"

// ----------------------------------------------------------------------------
class WhiteBishop : public GameObjectInsertion
{
    public:
        WhiteBishop( GameWindow *inputGameWindow, IntPoint position );
        WhiteBishop( GameWindow *inputGameWindow );
        ~WhiteBishop();
};



// ----------------------------------------------------------------------------