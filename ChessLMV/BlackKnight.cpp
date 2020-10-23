#include "BlackKnight.h"

// ----------------------------------------------------------------------------
BlackKnight::BlackKnight( GameWindow *inputGameWindow, IntPoint position ) :
        GameObjectInsertion( inputGameWindow )
{
    std::string strBuff("");
    getDataFromIni( strBuff, "blackKnight", "strTexture",
            ".\\Resources\\BlackKnight.png" );
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




BlackKnight::BlackKnight( GameWindow *inputGameWindow ) :
        GameObjectInsertion( inputGameWindow )
{
    std::string strBuff("");
    getDataFromIni( strBuff, "blackKnight", "strTexture",
            ".\\Resources\\BlackKnight.png" );
    m_gameWindow->m_fIsSuccess = m_gameWindow->strPngTextureToSdlTexture(
            m_sdlTexture, strBuff );

    if( m_gameWindow->m_fIsSuccess )
    {
        getDataFromIni( &(m_sdlRect->x), "blackKnight", "iPositionX", 140 );
        getDataFromIni( &(m_sdlRect->y), "blackKnight", "iPositionY", 140 );
        getDataFromIni( &(m_sdlRect->w), "blackKnight", "iWidth", 40 );
        getDataFromIni( &(m_sdlRect->h), "blackKnight", "iHeight", 40 );
        m_gameWindow->addObjectForRenderer( this );
    }
    else
    {
        setToLog( "BlackKnight texture didn't create." );
    }
}


// ----------------------------------------------------------------------------
BlackKnight::~BlackKnight()
{
    m_gameWindow->deleteObjectFromRenderer( this );
}



// ----------------------------------------------------------------------------