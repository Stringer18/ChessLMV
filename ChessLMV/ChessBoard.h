#pragma once

#include <SDL.h>

#include "GameObjectInsertion.h"
#include "GameWindow.h"
#include "HelpFunctions.hpp"
#include "CellBoard.h"

#include "BlackRook.h"
#include "BlackKnight.h"
#include "BlackBishop.h"
#include "BlackQueen.h"
#include "BlackKing.h"
#include "BlackPawn.h"
#include "WhitePawn.h"
#include "WhiteRook.h"
#include "WhiteKnight.h"
#include "WhiteBishop.h"
#include "WhiteQueen.h"
#include "WhiteKing.h"

#define _BOARD_SIZE_    8

// ----------------------------------------------------------------------------
class ChessBoard : public GameObjectInsertion
{
    public:
        ChessBoard( GameWindow *inputGameWindow );
        ~ChessBoard();

 //       bool addFigure( int iIndexX, int iIndexY, GameObject *pFigure);
 //       void delFigure( int iIndexX, int iIndexY );

    // ------------------------------------------------------------------------
    protected:
        // Prepares a grid of coordinates.
        void prepareGridBoard();

        // Creates and places figures.
        bool prepareFigures();

        // --------------------------------------------------------------------
        CellBoard m_board[_BOARD_SIZE_][_BOARD_SIZE_];

};



// ----------------------------------------------------------------------------