#pragma once

#include <SDL.h>

#include "GameObjectInsertion.h"
#include "GameWindow.h"
#include "HelpFunctions.hpp"

// ----------------------------------------------------------------------------
class WhitePawn : public GameObjectInsertion
{
    public:
        WhitePawn( GameWindow *inputGameWindow, IntPoint position );
        WhitePawn( GameWindow *inputGameWindow );
        ~WhitePawn();
};



// ----------------------------------------------------------------------------