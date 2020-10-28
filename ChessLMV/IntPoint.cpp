#include "IntPoint.h"


// ----------------------------------------------------------------------------
IntPoint::IntPoint( const int inputX /*= 0*/, const int inputY /*= 0*/ )
{ x = inputX; y = inputY; }



// ----------------------------------------------------------------------------
IntPoint IntPoint::plusPoint( const int plusX, const int plusY )
{ return IntPoint( x + plusX, y + plusY ); }


IntPoint IntPoint::plusPoint( const IntPoint &cPlusPoint )
{ return IntPoint( x + cPlusPoint.x, y + cPlusPoint.y ); }



// ----------------------------------------------------------------------------
bool operator== ( const IntPoint &point01, const IntPoint &point02 )
{ return ( ( point01.x == point02.x ) && ( point01.y == point02.y ) ); }


bool operator!= ( const IntPoint &point01, const IntPoint &point02 )
{ return !( point01 == point02 ); }


// ----------------------------------------------------------------------------