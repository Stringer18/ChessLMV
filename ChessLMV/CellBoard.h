#pragma once

#include "IntPoint.h"
#include "Figure.h"


// ----------------------------------------------------------------------------
class CellBoard
{
    public:
        CellBoard( int iPositionX = 0, int iPositionY = 0,
                Figure* pFigure = nullptr );

        void setPosition( IntPoint position );
        void setPosition( int iPositionX, int iPositionY );
        IntPoint getPosition();

        // --------------------------------------------------------------------
        Figure* m_pFigure;



    // ------------------------------------------------------------------------
    protected:
        IntPoint m_position;
};