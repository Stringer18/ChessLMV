#pragma once

#include <SDL.h>

#include "GameObjectInsertion.h"
#include "GameWindow.h"
#include "HelpFunctions.hpp"
#include "CellBoard.h"
#include "TextBox.h"

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


        // --------------------------------------------------------------------
        // Check the place of the click and performs actions based
        // on the context. This function is called when there was a click
        // to the board.
        void pushAnalysis( IntPoint pushPoint );

 //       bool addFigure( int iIndexX, int iIndexY, GameObject *pFigure);
 //       void delFigure( int iIndexX, int iIndexY );

    // ------------------------------------------------------------------------
    protected:
        // Change the current player (pass the move).
        void changeActualMove();




        // --------------------------------------------------------------------
        CellBoard m_board[_BOARD_SIZE_][_BOARD_SIZE_];

        // Whose turn is stored here. True - black, false - white.
        bool isBlackMove;
        TextBox *pTextNowBlack;
        TextBox *pTextNowWhite;



    // ------------------------------------------------------------------------
    private:
        // This function block prepares different elements of the board (board,
        // figures, etc.). The code has been moved out of the constructor into
        // separate functions for convenience and readability.
        // Use only from constructor.
        bool prepareBoard();
        void prepareGridBoard();
        bool prepareFigures();
        bool prepareText(); 
};



// ----------------------------------------------------------------------------