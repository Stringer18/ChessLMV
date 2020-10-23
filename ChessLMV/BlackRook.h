#pragma once

#include <SDL.h>

#include "GameObjectInsertion.h"
#include "GameWindow.h"
#include "HelpFunctions.hpp"

// ----------------------------------------------------------------------------
class BlackRook : public GameObjectInsertion
{
    public:
        BlackRook( GameWindow *inputGameWindow, IntPoint position );
        BlackRook( GameWindow *inputGameWindow );
        ~BlackRook();
};



// ----------------------------------------------------------------------------