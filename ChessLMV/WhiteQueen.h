#pragma once

#include <SDL.h>

#include "GameObjectInsertion.h"
#include "GameWindow.h"
#include "HelpFunctions.hpp"

// ----------------------------------------------------------------------------
class WhiteQueen : public GameObjectInsertion
{
    public:
        WhiteQueen( GameWindow *inputGameWindow, IntPoint position );
        WhiteQueen( GameWindow *inputGameWindow );
        ~WhiteQueen();
};



// ----------------------------------------------------------------------------