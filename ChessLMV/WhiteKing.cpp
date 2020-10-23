#include "WhiteKing.h"

// ----------------------------------------------------------------------------
WhiteKing::WhiteKing( GameWindow *inputGameWindow, IntPoint position ) :
        GameObjectInsertion( inputGameWindow )
{
    std::string strBuff("");
    getDataFromIni( strBuff, "whiteKing", "strTexture",
            ".\\Resources\\WhiteKing.png" );
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




WhiteKing::WhiteKing( GameWindow *inputGameWindow ) :
        GameObjectInsertion( inputGameWindow )
{
    std::string strBuff("");
    getDataFromIni( strBuff, "whiteKing", "strTexture",
            ".\\Resources\\WhiteKing.png" );
    m_gameWindow->m_fIsSuccess = m_gameWindow->strPngTextureToSdlTexture(
            m_sdlTexture, strBuff );

    if( m_gameWindow->m_fIsSuccess )
    {
        getDataFromIni( &(m_sdlRect->x), "whiteKing", "iPositionX", 140 );
        getDataFromIni( &(m_sdlRect->y), "whiteKing", "iPositionY", 140 );
        getDataFromIni( &(m_sdlRect->w), "whiteKing", "iWidth", 40 );
        getDataFromIni( &(m_sdlRect->h), "whiteKing", "iHeight", 40 );
        m_gameWindow->addObjectForRenderer( this );
    }
    else
    {
        setToLog( "WhiteKing texture didn't create." );
    }
}


// ----------------------------------------------------------------------------
WhiteKing::~WhiteKing()
{
    m_gameWindow->deleteObjectFromRenderer( this );
}



// ----------------------------------------------------------------------------