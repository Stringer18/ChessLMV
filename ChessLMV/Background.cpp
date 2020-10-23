#include "Background.h"

// ----------------------------------------------------------------------------
Background::Background( GameWindow *inputGameWindow ) :
        GameObjectInsertion( inputGameWindow )
{
    std::string strBuff("");
    getDataFromIni( strBuff, "gameWindow", "strTexture",
            ".\\Resources\\Background.png" );
    m_gameWindow->m_fIsSuccess = m_gameWindow->strPngTextureToSdlTexture(
            m_sdlTexture, strBuff );

    if( m_gameWindow->m_fIsSuccess )
    {
        m_sdlRect->x = 0;
        m_sdlRect->y = 0;
        getDataFromIni( &(m_sdlRect->w), "gameWindow", "iWidth", 800 );
        getDataFromIni( &(m_sdlRect->h), "gameWindow", "iHeight", 600 );
        m_gameWindow->addObjectForRenderer( this );
    }
    else
    {
        setToLog( "Background texture didn't create." );
    }
}



// ----------------------------------------------------------------------------
Background::~Background()
{
    m_gameWindow->deleteObjectFromRenderer( this );
}



// ----------------------------------------------------------------------------