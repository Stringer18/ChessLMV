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
                IntPoint position, Uint32 uiWidthSize, bool fIsVisible = false,
                int iFontSize = -1, SDL_Color *sdlColor = nullptr );
        ~TextBox();


        // --------------------------------------------------------------------
        // 
        void changeVisible();


        // --------------------------------------------------------------------
        bool getIsVisible();

    // ------------------------------------------------------------------------
    protected:
        bool m_fIsVisible;
};



// ----------------------------------------------------------------------------


 