#include "CellBoard.h"


// ----------------------------------------------------------------------------
CellBoard::CellBoard( int iPositionX /*= 0*/, int iPositionY /*= 0*/,
        GameObject* pFigure /*= nullptr*/ )
{
    m_position.x = iPositionX;
    m_position.y = iPositionY;
    m_pFigure = pFigure;
}



// ----------------------------------------------------------------------------
IntPoint CellBoard::getPosition() { return m_position; }



// ----------------------------------------------------------------------------
void CellBoard::setPosition( IntPoint position )
{
    m_position.x = position.x;
    m_position.y = position.y;
}


void CellBoard::setPosition( int iPositionX, int iPositionY )
{
    m_position.x = iPositionX;
    m_position.y = iPositionY;
}



// ----------------------------------------------------------------------------