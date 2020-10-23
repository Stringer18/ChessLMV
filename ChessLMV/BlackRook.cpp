#include "BlackRook.h"

// ----------------------------------------------------------------------------
BlackRook::BlackRook( GameWindow *inputGameWindow, IntPoint position ) :
        GameObjectInsertion( inputGameWindow )
{
    std::string strBuff("");
    getDataFromIni( strBuff, "blackRook", "strTexture",
            ".\\Resources\\BlackRook.png" );
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




BlackRook::BlackRook( GameWindow *inputGameWindow ) :
        GameObjectInsertion( inputGameWindow )
{
    std::string strBuff("");
    getDataFromIni( strBuff, "blackRook", "strTexture",
            ".\\Resources\\BlackRook.png" );
    m_gameWindow->m_fIsSuccess = m_gameWindow->strPngTextureToSdlTexture(
            m_sdlTexture, strBuff );

    if( m_gameWindow->m_fIsSuccess )
    {
        getDataFromIni( &(m_sdlRect->x), "blackRook", "iPositionX", 140 );
        getDataFromIni( &(m_sdlRect->y), "blackRook", "iPositionY", 140 );
        getDataFromIni( &(m_sdlRect->w), "blackRook", "iWidth", 40 );
        getDataFromIni( &(m_sdlRect->h), "blackRook", "iHeight", 40 );
        m_gameWindow->addObjectForRenderer( this );
    }
    else
    {
        setToLog( "BlackRook texture didn't create." );
    }
}


// ----------------------------------------------------------------------------
BlackRook::~BlackRook()
{
    m_gameWindow->deleteObjectFromRenderer( this );
}



// ----------------------------------------------------------------------------