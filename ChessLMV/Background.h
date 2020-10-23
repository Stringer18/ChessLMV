#pragma once

#include <SDL.h>

#include "GameObjectInsertion.h"
#include "GameWindow.h"
#include "HelpFunctions.hpp"

// ----------------------------------------------------------------------------
class Background : public GameObjectInsertion
{
    public:
        Background( GameWindow *inputGameWindow );
        ~Background();
};



// ----------------------------------------------------------------------------