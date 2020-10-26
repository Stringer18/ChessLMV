#pragma once

#include <SDL.h>
#include <math.h>

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
        ChessBoard( GameWindow *pGameWindow );
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
        // The function takes as an input the place of the click within the
        // board and returns the index (IntPoint) of the cell where this click
        // fell. If the value of any coordinate == -1 or 8, then we clicked
        // past the cells.
        IntPoint pushPointToCellPoint( IntPoint pushPoint );

        // Change the current player (pass the move).
        void changeActualMove();


        // --------------------------------------------------------------------
        CellBoard m_board[_BOARD_SIZE_][_BOARD_SIZE_];
        int m_iStepX, m_iStepY; // The step (size) of the squares of the board.

        // Whose turn is stored here. True - black, false - white.
        bool isBlackMove;
        TextBox *m_pTextNowBlack;
        TextBox *m_pTextNowWhite;

        // The index of the selected cell is stored here 
        // ( m_IndexCellSelection ). When no cell is selected, then the value
        // is == (-1, -1). It is indicator for know, is selection
        // ( m_pCellSelection ) visible or no.
        IntPoint m_IndexCellSelection;
        GameObject *m_pCellSelection;


    // ------------------------------------------------------------------------
    private:
        // This function block prepares different elements of the board (board,
        // figures, etc.). The code has been moved out of the constructor into
        // separate functions for convenience and readability.
        // Use only from constructor.
        bool prepareBoard();
        void prepareGridBoard();
        bool prepareCellSelection();
        bool prepareFigures();
        bool prepareText(); 
};



// ----------------------------------------------------------------------------