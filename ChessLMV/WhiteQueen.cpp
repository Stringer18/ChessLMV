#include "WhiteQueen.h"

// ----------------------------------------------------------------------------
WhiteQueen::WhiteQueen( GameWindow *inputGameWindow, IntPoint position ) :
        GameObjectInsertion( inputGameWindow )
{
    std::string strBuff("");
    getDataFromIni( strBuff, "whiteQueen", "strTexture",
            ".\\Resources\\WhiteQueen.png" );
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




WhiteQueen::WhiteQueen( GameWindow *inputGameWindow ) :
        GameObjectInsertion( inputGameWindow )
{
    std::string strBuff("");
    getDataFromIni( strBuff, "whiteQueen", "strTexture",
            ".\\Resources\\WhiteQueen.png" );
    m_gameWindow->m_fIsSuccess = m_gameWindow->strPngTextureToSdlTexture(
            m_sdlTexture, strBuff );

    if( m_gameWindow->m_fIsSuccess )
    {
        getDataFromIni( &(m_sdlRect->x), "whiteQueen", "iPositionX", 140 );
        getDataFromIni( &(m_sdlRect->y), "whiteQueen", "iPositionY", 140 );
        getDataFromIni( &(m_sdlRect->w), "whiteQueen", "iWidth", 40 );
        getDataFromIni( &(m_sdlRect->h), "whiteQueen", "iHeight", 40 );
        m_gameWindow->addObjectForRenderer( this );
    }
    else
    {
        setToLog( "WhiteQueen texture didn't create." );
    }
}


// ----------------------------------------------------------------------------
WhiteQueen::~WhiteQueen()
{
    m_gameWindow->deleteObjectFromRenderer( this );
}



// ----------------------------------------------------------------------------