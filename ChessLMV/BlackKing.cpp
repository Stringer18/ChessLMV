#include "BlackKing.h"

// ----------------------------------------------------------------------------
BlackKing::BlackKing( GameWindow *inputGameWindow, IntPoint position ) :
        GameObjectInsertion( inputGameWindow )
{
    std::string strBuff("");
    getDataFromIni( strBuff, "blackKing", "strTexture",
            ".\\Resources\\BlackKing.png" );
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




BlackKing::BlackKing( GameWindow *inputGameWindow ) :
        GameObjectInsertion( inputGameWindow )
{
    std::string strBuff("");
    getDataFromIni( strBuff, "blackKing", "strTexture",
            ".\\Resources\\BlackKing.png" );
    m_gameWindow->m_fIsSuccess = m_gameWindow->strPngTextureToSdlTexture(
            m_sdlTexture, strBuff );

    if( m_gameWindow->m_fIsSuccess )
    {
        getDataFromIni( &(m_sdlRect->x), "blackKing", "iPositionX", 140 );
        getDataFromIni( &(m_sdlRect->y), "blackKing", "iPositionY", 140 );
        getDataFromIni( &(m_sdlRect->w), "blackKing", "iWidth", 40 );
        getDataFromIni( &(m_sdlRect->h), "blackKing", "iHeight", 40 );
        m_gameWindow->addObjectForRenderer( this );
    }
    else
    {
        setToLog( "BlackKing texture didn't create." );
    }
}


// ----------------------------------------------------------------------------
BlackKing::~BlackKing()
{
    m_gameWindow->deleteObjectFromRenderer( this );
}



// ----------------------------------------------------------------------------