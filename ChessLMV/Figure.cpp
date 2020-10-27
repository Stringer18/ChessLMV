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