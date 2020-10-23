#include "WhiteRook.h"

// ----------------------------------------------------------------------------
WhiteRook::WhiteRook( GameWindow *inputGameWindow, IntPoint position ) :
        GameObjectInsertion( inputGameWindow )
{
    std::string strBuff("");
    getDataFromIni( strBuff, "whiteRook", "strTexture",
            ".\\Resources\\WhiteRook.png" );
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




WhiteRook::WhiteRook( GameWindow *inputGameWindow ) :
        GameObjectInsertion( inputGameWindow )
{
    std::string strBuff("");
    getDataFromIni( strBuff, "whiteRook", "strTexture",
            ".\\Resources\\WhiteRook.png" );
    m_gameWindow->m_fIsSuccess = m_gameWindow->strPngTextureToSdlTexture(
            m_sdlTexture, strBuff );

    if( m_gameWindow->m_fIsSuccess )
    {
        getDataFromIni( &(m_sdlRect->x), "whiteRook", "iPositionX", 140 );
        getDataFromIni( &(m_sdlRect->y), "whiteRook", "iPositionY", 140 );
        getDataFromIni( &(m_sdlRect->w), "whiteRook", "iWidth", 40 );
        getDataFromIni( &(m_sdlRect->h), "whiteRook", "iHeight", 40 );
        m_gameWindow->addObjectForRenderer( this );
    }
    else
    {
        setToLog( "WhiteRook texture didn't create." );
    }
}


// ----------------------------------------------------------------------------
WhiteRook::~WhiteRook()
{
    m_gameWindow->deleteObjectFromRenderer( this );
}



// ----------------------------------------------------------------------------