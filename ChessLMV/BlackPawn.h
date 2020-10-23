#pragma once

#include <SDL.h>

#include "GameObjectInsertion.h"
#include "GameWindow.h"
#include "HelpFunctions.hpp"

// ----------------------------------------------------------------------------
class BlackPawn : public GameObjectInsertion
{
    public:
        BlackPawn( GameWindow *inputGameWindow, IntPoint position );
        BlackPawn( GameWindow *inputGameWindow );
        ~BlackPawn();
};



// ----------------------------------------------------------------------------