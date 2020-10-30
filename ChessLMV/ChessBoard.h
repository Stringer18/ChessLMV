#pragma once

#include <SDL.h>
#include <math.h>

#include "GameObjectInsertion.h"
#include "GameWindow.h"
#include "HelpFunctions.hpp"
#include "CellBoard.h"
#include "TextBox.h"
#include "Figure.h"


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


        // --------------------------------------------------------------------
        bool isOnBoardIndex( IntPoint checkIndex );


    // ------------------------------------------------------------------------
    protected:
        // The function takes as an input the place of the click within the
        // board and returns the index (IntPoint) of the cell where this click
        // fell. If the value of any coordinate == -1 or 8, then we clicked
        // past the cells.
        IntPoint pushPointToCellPoint( IntPoint pushPoint );


        // --------------------------------------------------------------------
        // Change the current player (pass the move).
        void changeActualMove();


        // --------------------------------------------------------------------
        void selectFigure( IntPoint pushIndex );
        void deselectFigure();

        // We perform attack or move actions only with a selected figure.
        bool checkMoveFigure( IntPoint selectIndex, IntPoint finishIndex );
        void moveFigure( IntPoint pushIndex );
        void atackFigure( IntPoint atackIndex );


        // --------------------------------------------------------------------
        // There are special rules

        // Promotion of a pawn on the 8th line of the board.
        void pawnPromotion( IntPoint pushIndex );

        // "Taking on the pass". Attacking the opponent's pawn with his pawn
        // after it has moved 2 cells.
        void pawnTakingPass( IntPoint pushIndex );

        // Check the castling and do it if it can.
        void kingCastling( IntPoint pushIndex );


        // --------------------------------------------------------------------
        // Checks if the king is in check if he is standing in the checked
        // cell. If return true - danger.
        bool checkCheck( IntPoint checkIndex );


        // --------------------------------------------------------------------
        // Checks if the king is in check.
        bool checkCheckKing();


        // --------------------------------------------------------------------
        // Finds the king and returns the index of the square where it stands.
        IntPoint findKing();


        // --------------------------------------------------------------------
        CellBoard m_board[_BOARD_SIZE_][_BOARD_SIZE_];
        int m_iStepX, m_iStepY; // The step (size) of the squares of the board.


        // --------------------------------------------------------------------
        // Whose turn is stored here. True - black, false - white.
        bool m_isBlackMove;
        TextBox *m_pTextNowBlack;
        TextBox *m_pTextNowWhite;


        // --------------------------------------------------------------------
        // The index of the selected cell is stored here 
        // ( m_IndexCellSelection ). When no cell is selected, then the value
        // is == (-1, -1). It is indicator for know, is selection
        // ( m_pCellSelection ) visible or no.
        IntPoint m_IndexCellSelection;
        GameObject *m_pCellSelection;


        // --------------------------------------------------------------------
        // If this flag is up, it means that some pawn has reached the 8th line
        // and a special rule is activated - "pawn promotion". All clicks on
        // the board are ignored until a selection is made of a figure to
        // transform.
        bool m_fIsPawnPromotionActive;
        int iIndexXStartSelectionPawnPromotion;
        TextBox *m_pTextChangePawn;
        GameObject *m_pBlackPawnPromotion;
        GameObject *m_pWhitePawnPromotion;


        // --------------------------------------------------------------------
        // These two variables are needed only so that we can check the
        // "taking on the pass".
        IntPoint m_lastMoveFrom;
        IntPoint m_lastMoveTo;


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
        bool preparePawnPromotion();
};



// ----------------------------------------------------------------------------