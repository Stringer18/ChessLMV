#pragma once

#include <SDL.h>
#include <math.h>

#include "GameObjectInsertion.h"
#include "GameWindow.h"
#include "HelpFunctions.hpp"


enum defineFigureType : int
{
    _PAWN_ = 0,
    _ROOK_,
    _KNIGHT_,
    _BISHOP_,
    _QUEEN_,
    _KING_,

    _FIGURE_TYPE_MAX_
};

// ----------------------------------------------------------------------------
class Figure : public GameObjectInsertion
{
    public:
        Figure( GameWindow *pGameWindow, bool fIsBlackFigure, int iTypeFigure,
                IntPoint position );
        ~Figure();

        void setPosition( const IntPoint position );
        void setPosition( int iX, int iY );


        // --------------------------------------------------------------------
        // Return:  Black -> true    White -> false
        bool getColor();

        int getType();
        bool getIsMoved();

        // --------------------------------------------------------------------
        // A wrapper for choosing which function to check the resolution of
        // the trajectory of moving.
        IntPoint checkTrajectory( IntPoint selectedIndex, IntPoint pushIndex,
                Figure *pushFigure );


    // ------------------------------------------------------------------------
    protected:
        bool m_fIsBlackFigure;
        int m_iTypeFigure;
        bool m_fIsMoved;


    // ------------------------------------------------------------------------
    private:
        // There is a large block for selecting the path (in string) to the
        // file with the texture of the desired figure. If it cannot find the
        // required item, it will return an empty string and assign
        // m_gameWindow->m_fIsSuccess = false.
        std::string selectStrTexture();

        // --------------------------------------------------------------------
        // These functions check if the moving path is allowed for a particular
        // figure type. There is no function for the Queen because it is the
        // sum of Rook and Bishop.
        IntPoint checkTrajectoryPawn( IntPoint selectedIndex,
                IntPoint pushIndex, Figure *pushFigure );
        IntPoint checkTrajectoryRook( IntPoint selectedIndex,
                IntPoint pushIndex );
        IntPoint checkTrajectoryKnight( IntPoint selectedIndex,
                IntPoint pushIndex );
        IntPoint checkTrajectoryBishop( IntPoint selectedIndex,
                IntPoint pushIndex );
        IntPoint checkTrajectoryKing( IntPoint selectedIndex,
                IntPoint pushIndex );
};



// ----------------------------------------------------------------------------