#include "BlackPawn.h"

// ----------------------------------------------------------------------------
BlackPawn::BlackPawn( GameWindow *inputGameWindow, IntPoint position ) :
        GameObjectInsertion( inputGameWindow )
{
    std::string strBuff("");
    getDataFromIni( strBuff, "blackPawn", "strTexture",
            ".\\Resources\\BlackPawn.png" );
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




BlackPawn::BlackPawn( GameWindow *inputGameWindow ) :
        GameObjectInsertion( inputGameWindow )
{
    std::string strBuff("");
    getDataFromIni( strBuff, "blackPawn", "strTexture",
            ".\\Resources\\BlackPawn.png" );
    m_gameWindow->m_fIsSuccess = m_gameWindow->strPngTextureToSdlTexture(
            m_sdlTexture, strBuff );

    if( m_gameWindow->m_fIsSuccess )
    {
        getDataFromIni( &(m_sdlRect->x), "blackPawn", "iPositionX", 140 );
        getDataFromIni( &(m_sdlRect->y), "blackPawn", "iPositionY", 140 );
        getDataFromIni( &(m_sdlRect->w), "blackPawn", "iWidth", 40 );
        getDataFromIni( &(m_sdlRect->h), "blackPawn", "iHeight", 40 );
        m_gameWindow->addObjectForRenderer( this );
    }
    else
    {
        setToLog( "BlackPawn texture didn't create." );
    }
}


// ----------------------------------------------------------------------------
BlackPawn::~BlackPawn()
{
    m_gameWindow->deleteObjectFromRenderer( this );
}



// ----------------------------------------------------------------------------