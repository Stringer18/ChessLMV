#include "Figure.h"

// ----------------------------------------------------------------------------
Figure::Figure( GameWindow *pGameWindow, bool fIsBlackFigure, int iTypeFigure,
                IntPoint position ) : GameObjectInsertion( pGameWindow )
{
    m_fIsBlackFigure = fIsBlackFigure;
    m_iTypeFigure = iTypeFigure;

    std::string strBuff = selectStrTexture();
    if( m_gameWindow->m_fIsSuccess )
    {
        m_gameWindow->m_fIsSuccess = m_gameWindow->strPngTextureToSdlTexture(
                m_sdlTexture, strBuff );
    }

    if( m_gameWindow->m_fIsSuccess )
    {
        setPosition( position );
        m_fIsMoved = false;
        getDataFromIni( &(m_sdlRect->w), "figure", "iWidth", 40 );
        getDataFromIni( &(m_sdlRect->h), "figure", "iHeight", 40 );
        m_gameWindow->addObjectForRenderer( this );
    }
    else
    {
        setToLog( std::string( "Figure didn't create." ) +
                        "\n\tIs Black == " + toString( m_fIsBlackFigure ) +
                        "\n\tType == " + toString( m_iTypeFigure ) );
    }
}



// ----------------------------------------------------------------------------
Figure::~Figure()
{
    m_gameWindow->deleteObjectFromRenderer( this );
}



// ----------------------------------------------------------------------------
void Figure::setPosition( const IntPoint position )
{
    m_sdlRect->x = position.x;
    m_sdlRect->y = position.y;
    m_fIsMoved = true;
}

void Figure::setPosition( int iX, int iY )
{
    m_sdlRect->x = iX;
    m_sdlRect->y = iY;
    m_fIsMoved = true;
}




// ----------------------------------------------------------------------------
bool Figure::getColor() { return m_fIsBlackFigure; }
int Figure::getType() { return m_iTypeFigure; }


// ----------------------------------------------------------------------------
IntPoint Figure::checkTrajectory( IntPoint selectedIndex, IntPoint pushIndex,
        Figure *pushFigure )
{
    switch( m_iTypeFigure )
    {
        case _PAWN_:
        {
            return checkTrajectoryPawn( selectedIndex, pushIndex, pushFigure );
            //break;
        }
        case _ROOK_:
        {
            return checkTrajectoryRook( selectedIndex, pushIndex ); //break;
        }
        case _KNIGHT_:
        {
            return checkTrajectoryKnight( selectedIndex, pushIndex ); //break;
        }
        case _BISHOP_:
        {
            return checkTrajectoryBishop( selectedIndex, pushIndex ); //break;
        }
        case _QUEEN_:
        {
            IntPoint buff = checkTrajectoryRook( selectedIndex, pushIndex );
            if( abs( buff.x ) + abs( buff.y ) != 0 ) { return buff; }
            return ( checkTrajectoryBishop( selectedIndex, pushIndex ) );
            //break;
        }
        case _KING_:
        {
            return checkTrajectoryKing( selectedIndex, pushIndex ); //break;
        }
        default:
        {
            setToLog( "An attempt was made to move an unknown figure." );
            return ( 0, 0 ); //break;
        }
    }
}



// ----------------------------------------------------------------------------
std::string Figure::selectStrTexture()
{
    std::string strBuff("");
    if( m_fIsBlackFigure )
    {
        switch( m_iTypeFigure )
        {
            case _PAWN_:
            {
                getDataFromIni( strBuff, "figure", "strBlackPawnTexture",
                        ".\\Resources\\BlackPawn.png" );
                break;
            }
            case _ROOK_:
            {
                getDataFromIni( strBuff, "figure", "strBlackRookTexture",
                        ".\\Resources\\BlackRook.png" );
                break;
            }
            case _KNIGHT_:
            {
                getDataFromIni( strBuff, "figure", "strBlackKnightTexture",
                        ".\\Resources\\BlackKnight.png" );
                break;
            }
            case _BISHOP_:
            {
                getDataFromIni( strBuff, "figure", "strBlackBishopTexture",
                        ".\\Resources\\BlackBishop.png" );
                break;
            }
            case _QUEEN_:
            {
                getDataFromIni( strBuff, "figure", "strBlackQueenTexture",
                        ".\\Resources\\BlackQueen.png" );
                break;
            }
            case _KING_:
            {
                getDataFromIni( strBuff, "figure", "strBlackKingTexture",
                        ".\\Resources\\BlackKing.png" );
                break;
            }
            default:
            {
                setToLog( std::string( "Unknown type of figure." ) +
                        "\n\tIs Black == " + toString( m_fIsBlackFigure ) +
                        "\n\tType == " + toString( m_iTypeFigure ) );
                m_gameWindow->m_fIsSuccess = false;
                break;
            }
        }
    }
    else
    {
        switch( m_iTypeFigure )
        {
            case _PAWN_:
            {
                getDataFromIni( strBuff, "figure", "strWhitePawnTexture",
                        ".\\Resources\\WhitePawn.png" );
                break;
            }
            case _ROOK_:
            {
                getDataFromIni( strBuff, "figure", "strWhiteRookTexture",
                        ".\\Resources\\WhiteRook.png" );
                break;
            }
            case _KNIGHT_:
            {
                getDataFromIni( strBuff, "figure", "strWhiteKnightTexture",
                        ".\\Resources\\WhiteKnight.png" );
                break;
            }
            case _BISHOP_:
            {
                getDataFromIni( strBuff, "figure", "strWhiteBishopTexture",
                        ".\\Resources\\WhiteBishop.png" );
                break;
            }
            case _QUEEN_:
            {
                getDataFromIni( strBuff, "figure", "strWhiteQueenTexture",
                        ".\\Resources\\WhiteQueen.png" );
                break;
            }
            case _KING_:
            {
                getDataFromIni( strBuff, "figure", "strWhiteKingTexture",
                        ".\\Resources\\WhiteKing.png" );
                break;
            }
            default:
            {
                setToLog( std::string( "Unknown type of figure." ) +
                        "\n\tIs Black == " + toString( m_fIsBlackFigure ) +
                        "\n\tType == " + toString( m_iTypeFigure ) );
                m_gameWindow->m_fIsSuccess = false;
                break;
            }
        }
    }
    return strBuff;
}



// ----------------------------------------------------------------------------
IntPoint Figure::checkTrajectoryPawn( IntPoint selectedIndex, IntPoint pushIndex,
        Figure *pushFigure )
{
    IntPoint moveVector( 0, 0 );
    int iDeltaX = pushIndex.x - selectedIndex.x;
    int iDeltaY = pushIndex.y - selectedIndex.y;
    
    if( pushFigure == nullptr ) 
    {
        if( iDeltaX == 0 )
        {
            if( m_fIsMoved )
            {
                if( iDeltaY == ( m_fIsBlackFigure ? 1 : -1 ) )
                {
                    moveVector.y = iDeltaY;
                }
            }
            else
            {
                if( m_fIsBlackFigure ?
                        ( ( iDeltaY == 1 ) || ( iDeltaY == 2 ) ) :
                        ( ( iDeltaY == -1 ) || ( iDeltaY == -2 ) ) )
                {
                    moveVector.y = iDeltaY / abs( iDeltaY );
                }
            }
        }
    }
    else
    {
        if( ( abs( iDeltaX ) == 1 ) && ( iDeltaY ==
                ( m_fIsBlackFigure ? 1 : -1 ) ) ) 
        {
            moveVector.x = iDeltaX;
            moveVector.y = iDeltaY;
        }
    }
    return moveVector;
}



// ----------------------------------------------------------------------------
IntPoint Figure::checkTrajectoryRook( IntPoint selectedIndex,
        IntPoint pushIndex )
{
    IntPoint moveVector( 0, 0 );
    int iDeltaX = pushIndex.x - selectedIndex.x;
    int iDeltaY = pushIndex.y - selectedIndex.y;
    if( ( ( abs( iDeltaX ) == 0 ) && ( abs( iDeltaY ) != 0 ) ) ||
            ( ( abs( iDeltaX ) != 0 ) && ( abs( iDeltaY ) == 0 ) ) )
    {
        if( iDeltaX != 0 ) { moveVector.x = iDeltaX / abs( iDeltaX ); }
        if( iDeltaY != 0 ) { moveVector.y = iDeltaY / abs( iDeltaY ); }
    }
    return moveVector;
}



// ----------------------------------------------------------------------------
IntPoint Figure::checkTrajectoryKnight( IntPoint selectedIndex,
        IntPoint pushIndex)
{
    IntPoint moveVector( 0, 0 );
    int iDeltaX = pushIndex.x - selectedIndex.x;
    int iDeltaY = pushIndex.y - selectedIndex.y;
    if( ( ( abs( iDeltaX ) + abs( iDeltaY ) ) == 3 ) &&
            ( abs( iDeltaX ) != 0 ) && ( abs( iDeltaY ) != 0 ) )
    {
        moveVector.x = iDeltaX;
        moveVector.y = iDeltaY;
    }
    return moveVector;
}



// ----------------------------------------------------------------------------
IntPoint Figure::checkTrajectoryBishop( IntPoint selectedIndex,
        IntPoint pushIndex)
{
    IntPoint moveVector( 0, 0 );
    int iDeltaX = pushIndex.x - selectedIndex.x;
    int iDeltaY = pushIndex.y - selectedIndex.y;
    if( abs( iDeltaX ) == abs( iDeltaY ) )
    {
        if( iDeltaX != 0 ) { moveVector.x = iDeltaX / abs( iDeltaX ); }
        if( iDeltaY != 0 ) { moveVector.y = iDeltaY / abs( iDeltaY ); }
    }
    return moveVector;
}



// ----------------------------------------------------------------------------
IntPoint Figure::checkTrajectoryKing( IntPoint selectedIndex,
        IntPoint pushIndex )
{
    IntPoint moveVector( 0, 0 );
    int iDeltaX = pushIndex.x - selectedIndex.x;
    int iDeltaY = pushIndex.y - selectedIndex.y;
    if( ( abs( iDeltaX ) <= 1 ) && ( abs( iDeltaY ) <= 1 ) )
    {
        moveVector.x = iDeltaX;
        moveVector.y = iDeltaY;
    }
    return moveVector;
}



// ----------------------------------------------------------------------------