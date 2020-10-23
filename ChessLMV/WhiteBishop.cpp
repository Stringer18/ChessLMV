#include "WhiteBishop.h"

// ----------------------------------------------------------------------------
WhiteBishop::WhiteBishop( GameWindow *inputGameWindow, IntPoint position ) :
        GameObjectInsertion( inputGameWindow )
{
    std::string strBuff("");
    getDataFromIni( strBuff, "whiteBishop", "strTexture",
            ".\\Resources\\WhiteBishop.png" );
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




WhiteBishop::WhiteBishop( GameWindow *inputGameWindow ) :
        GameObjectInsertion( inputGameWindow )
{
    std::string strBuff("");
    getDataFromIni( strBuff, "whiteBishop", "strTexture",
            ".\\Resources\\WhiteBishop.png" );
    m_gameWindow->m_fIsSuccess = m_gameWindow->strPngTextureToSdlTexture(
            m_sdlTexture, strBuff );

    if( m_gameWindow->m_fIsSuccess )
    {
        getDataFromIni( &(m_sdlRect->x), "whiteBishop", "iPositionX", 140 );
        getDataFromIni( &(m_sdlRect->y), "whiteBishop", "iPositionY", 140 );
        getDataFromIni( &(m_sdlRect->w), "whiteBishop", "iWidth", 40 );
        getDataFromIni( &(m_sdlRect->h), "whiteBishop", "iHeight", 40 );
        m_gameWindow->addObjectForRenderer( this );
    }
    else
    {
        setToLog( "WhiteBishop texture didn't create." );
    }
}


// ----------------------------------------------------------------------------
WhiteBishop::~WhiteBishop()
{
    m_gameWindow->deleteObjectFromRenderer( this );
}



// ----------------------------------------------------------------------------