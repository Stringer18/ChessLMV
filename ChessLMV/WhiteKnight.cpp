#include "WhiteKnight.h"

// ----------------------------------------------------------------------------
WhiteKnight::WhiteKnight( GameWindow *inputGameWindow, IntPoint position ) :
        GameObjectInsertion( inputGameWindow )
{
    std::string strBuff("");
    getDataFromIni( strBuff, "whiteKnight", "strTexture",
            ".\\Resources\\WhiteKnight.png" );
    m_gameWindow->m_fIsSuccess = m_gameWindow->strPngTextureToSdlTexture(
            m_sdlTexture, strBuff );

    if( m_gameWindow->m_fIsSuccess )
    {
        setPosition( position );
        getDataFromIni( &(m_sdlRect->w), "figure", "iWidth", 40 );
        getDataFromIni( &(m_sdlRect->h), "figure", "iHeight", 40 );
        m_gameWindow->addObjectForRenderer( this );
    }
    else
    {
        setToLog( "Black Rook texture didn't create." );
    }
}




WhiteKnight::WhiteKnight( GameWindow *inputGameWindow ) :
        GameObjectInsertion( inputGameWindow )
{
    std::string strBuff("");
    getDataFromIni( strBuff, "whiteKnight", "strTexture",
            ".\\Resources\\WhiteKnight.png" );
    m_gameWindow->m_fIsSuccess = m_gameWindow->strPngTextureToSdlTexture(
            m_sdlTexture, strBuff );

    if( m_gameWindow->m_fIsSuccess )
    {
        getDataFromIni( &(m_sdlRect->x), "whiteKnight", "iPositionX", 140 );
        getDataFromIni( &(m_sdlRect->y), "whiteKnight", "iPositionY", 140 );
        getDataFromIni( &(m_sdlRect->w), "whiteKnight", "iWidth", 40 );
        getDataFromIni( &(m_sdlRect->h), "whiteKnight", "iHeight", 40 );
        m_gameWindow->addObjectForRenderer( this );
    }
    else
    {
        setToLog( "WhiteKnight texture didn't create." );
    }
}


// ----------------------------------------------------------------------------
WhiteKnight::~WhiteKnight()
{
    m_gameWindow->deleteObjectFromRenderer( this );
}



// ----------------------------------------------------------------------------