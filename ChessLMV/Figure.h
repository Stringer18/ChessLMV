#pragma once

#include <SDL.h>

#include "GameObjectInsertion.h"
#include "GameWindow.h"
#include "HelpFunctions.hpp"


#define _PAWN_      0
#define _ROOK_      1
#define _KNIGHT_    2
#define _BISHOP_    3
#define _QUEEN_     4
#define _KING_      5


// ----------------------------------------------------------------------------
class Figure : public GameObjectInsertion
{
    public:
        Figure( GameWindow *pGameWindow, bool fIsBlackFigure, int iTypeFigure,
                IntPoint position );
        ~Figure();


    // ------------------------------------------------------------------------
    protected:
        bool m_fIsBlackFigure;
        int m_iTypeFigure;


    // ------------------------------------------------------------------------
    private:
        // There is a large block for selecting the path (in string) to the
        // file with the texture of the desired figure. If it cannot find the
        // required item, it will return an empty string and assign
        // m_gameWindow->m_fIsSuccess = false.
        std::string selectStrTexture();
};



// ----------------------------------------------------------------------------