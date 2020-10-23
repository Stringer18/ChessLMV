#pragma once

#include "IntPoint.h"
#include "GameObject.h"


// ----------------------------------------------------------------------------
class CellBoard
{
    public:
        CellBoard( int iPositionX = 0, int iPositionY = 0,
                GameObject* pFigure = nullptr );

        void setPosition( IntPoint position );
        void setPosition( int iPositionX, int iPositionY );
        IntPoint getPosition();

        // --------------------------------------------------------------------
        GameObject* m_pFigure;



    // ------------------------------------------------------------------------
    protected:
        IntPoint m_position;
};