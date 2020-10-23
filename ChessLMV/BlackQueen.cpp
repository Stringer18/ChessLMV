#include "BlackQueen.h"

// ----------------------------------------------------------------------------
BlackQueen::BlackQueen( GameWindow *inputGameWindow, IntPoint position ) :
        GameObjectInsertion( inputGameWindow )
{
    std::string strBuff("");
    getDataFromIni( strBuff, "blackQueen", "strTexture",
            ".\\Resources\\BlackQueen.png" );
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




BlackQueen::BlackQueen( GameWindow *inputGameWindow ) :
        GameObjectInsertion( inputGameWindow )
{
    std::string strBuff("");
    getDataFromIni( strBuff, "blackQueen", "strTexture",
            ".\\Resources\\BlackQueen.png" );
    m_gameWindow->m_fIsSuccess = m_gameWindow->strPngTextureToSdlTexture(
            m_sdlTexture, strBuff );

    if( m_gameWindow->m_fIsSuccess )
    {
        getDataFromIni( &(m_sdlRect->x), "blackQueen", "iPositionX", 140 );
        getDataFromIni( &(m_sdlRect->y), "blackQueen", "iPositionY", 140 );
        getDataFromIni( &(m_sdlRect->w), "blackQueen", "iWidth", 40 );
        getDataFromIni( &(m_sdlRect->h), "blackQueen", "iHeight", 40 );
        m_gameWindow->addObjectForRenderer( this );
    }
    else
    {
        setToLog( "BlackQueen texture didn't create." );
    }
}


// ----------------------------------------------------------------------------
BlackQueen::~BlackQueen()
{
    m_gameWindow->deleteObjectFromRenderer( this );
}



// ----------------------------------------------------------------------------