#pragma once

#include <SDL.h>

#include "GameObjectInsertion.h"
#include "GameWindow.h"
#include "HelpFunctions.hpp"

// ----------------------------------------------------------------------------
class WhiteRook : public GameObjectInsertion
{
    public:
        WhiteRook( GameWindow *inputGameWindow, IntPoint position );
        WhiteRook( GameWindow *inputGameWindow );
        ~WhiteRook();
};



// ----------------------------------------------------------------------------