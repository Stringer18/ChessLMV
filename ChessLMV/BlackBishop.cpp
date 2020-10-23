#include "BlackBishop.h"

// ----------------------------------------------------------------------------
BlackBishop::BlackBishop( GameWindow *inputGameWindow, IntPoint position ) :
        GameObjectInsertion( inputGameWindow )
{
    std::string strBuff("");
    getDataFromIni( strBuff, "blackBishop", "strTexture",
            ".\\Resources\\BlackBishop.png" );
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




BlackBishop::BlackBishop( GameWindow *inputGameWindow ) :
        GameObjectInsertion( inputGameWindow )
{
    std::string strBuff("");
    getDataFromIni( strBuff, "blackBishop", "strTexture",
            ".\\Resources\\BlackBishop.png" );
    m_gameWindow->m_fIsSuccess = m_gameWindow->strPngTextureToSdlTexture(
            m_sdlTexture, strBuff );

    if( m_gameWindow->m_fIsSuccess )
    {
        getDataFromIni( &(m_sdlRect->x), "blackBishop", "iPositionX", 140 );
        getDataFromIni( &(m_sdlRect->y), "blackBishop", "iPositionY", 140 );
        getDataFromIni( &(m_sdlRect->w), "blackBishop", "iWidth", 40 );
        getDataFromIni( &(m_sdlRect->h), "blackBishop", "iHeight", 40 );
        m_gameWindow->addObjectForRenderer( this );
    }
    else
    {
        setToLog( "BlackBishop texture didn't create." );
    }
}


// ----------------------------------------------------------------------------
BlackBishop::~BlackBishop()
{
    m_gameWindow->deleteObjectFromRenderer( this );
}



// ----------------------------------------------------------------------------