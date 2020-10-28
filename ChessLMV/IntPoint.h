#pragma once

// ----------------------------------------------------------------------------
class IntPoint
{
    public:
        IntPoint( const int inputX = 0, const int inputY = 0 );

        IntPoint plusPoint( const int plusX, const int plusY );
        IntPoint plusPoint( const IntPoint &cPlusPoint );


        friend bool operator== ( const IntPoint &point01,
                const IntPoint &point02 );
        friend bool operator!= ( const IntPoint &point01,
                const IntPoint &point02 );

        int x;
        int y;
};
// ----------------------------------------------------------------------------