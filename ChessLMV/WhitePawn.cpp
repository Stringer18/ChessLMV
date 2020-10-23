#include "WhitePawn.h"

// ----------------------------------------------------------------------------
WhitePawn::WhitePawn( GameWindow *inputGameWindow, IntPoint position ) :
        GameObjectInsertion( inputGameWindow )
{
    std::string strBuff("");
    getDataFromIni( strBuff, "whitePawn", "strTexture",
            ".\\Resources\\WhitePawn.png" );
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




WhitePawn::WhitePawn( GameWindow *inputGameWindow ) :
        GameObjectInsertion( inputGameWindow )
{
    std::string strBuff("");
    getDataFromIni( strBuff, "whitePawn", "strTexture",
            ".\\Resources\\WhitePawn.png" );
    m_gameWindow->m_fIsSuccess = m_gameWindow->strPngTextureToSdlTexture(
            m_sdlTexture, strBuff );

    if( m_gameWindow->m_fIsSuccess )
    {
        getDataFromIni( &(m_sdlRect->x), "whitePawn", "iPositionX", 140 );
        getDataFromIni( &(m_sdlRect->y), "whitePawn", "iPositionY", 140 );
        getDataFromIni( &(m_sdlRect->w), "whitePawn", "iWidth", 40 );
        getDataFromIni( &(m_sdlRect->h), "whitePawn", "iHeight", 40 );
        m_gameWindow->addObjectForRenderer( this );
    }
    else
    {
        setToLog( "WhitePawn texture didn't create." );
    }
}


// ----------------------------------------------------------------------------
WhitePawn::~WhitePawn()
{
    m_gameWindow->deleteObjectFromRenderer( this );
}



// ----------------------------------------------------------------------------