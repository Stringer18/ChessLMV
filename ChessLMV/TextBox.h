#pragma once

#include <SDL.h>

#include "GameObjectInsertion.h"
#include "GameWindow.h"
#include "HelpFunctions.hpp"

// ----------------------------------------------------------------------------
class TextBox : public GameObjectInsertion
{
    public:
        TextBox( GameWindow *inputGameWindow, std::string strMessage,
                IntPoint position, bool fIsVisible = false, int iFontSize = -1,
                SDL_Color *sdlColor = nullptr );
        //TextBox( GameWindow *inputGameWindow, bool fIsVisible = false );
        ~TextBox();


    // ------------------------------------------------------------------------
    protected:
        std::string m_strMessage;
        bool m_fIsVisible;
};



// ----------------------------------------------------------------------------


 