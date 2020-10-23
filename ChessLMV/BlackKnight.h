#pragma once

#include <SDL.h>

#include "GameObjectInsertion.h"
#include "GameWindow.h"
#include "HelpFunctions.hpp"

// ----------------------------------------------------------------------------
class BlackKnight : public GameObjectInsertion
{
    public:
        BlackKnight( GameWindow *inputGameWindow, IntPoint position );
        BlackKnight( GameWindow *inputGameWindow );
        ~BlackKnight();
};



// ----------------------------------------------------------------------------