#include "TextBox.h"

// ----------------------------------------------------------------------------
TextBox::TextBox( GameWindow *inputGameWindow, std::string strMessage,
        IntPoint position, bool fIsVisible /*= false*/, int iFontSize /*= -1*/,
        SDL_Color *sdlColor /*= nullptr*/ ) :
                GameObjectInsertion( inputGameWindow )
{
    m_strMessage = strMessage;
    m_fIsVisible = fIsVisible;

    m_gameWindow->m_fIsSuccess = m_gameWindow->strTextToSdlTexture(
            m_sdlTexture, m_strMessage, iFontSize, sdlColor );

    if( m_gameWindow->m_fIsSuccess )
    {
        setPosition( position );
        SDL_QueryTexture( m_sdlTexture, NULL, NULL, &(m_sdlRect->w), &(m_sdlRect->h) );
        if( m_fIsVisible ) { m_gameWindow->addObjectForRenderer( this ); }
    }
    else
    {
        setToLog( "TextBox texture didn't create." );
    }
}




//TextBox::TextBox( GameWindow *inputGameWindow, bool fIsVisible /*= false*/ ) :
//        GameObjectInsertion( inputGameWindow )
//{
//    m_fIsVisible = fIsVisible;
//
//    std::string strBuff("");
//    getDataFromIni( strBuff, "whitePawn", "strTexture",
//            ".\\Resources\\WhitePawn.png" );
//    m_gameWindow->m_fIsSuccess = m_gameWindow->strPngTextureToSdlTexture(
//            m_sdlTexture, strBuff );
//
//    if( m_gameWindow->m_fIsSuccess )
//    {
//        getDataFromIni( &(m_sdlRect->x), "whitePawn", "iPositionX", 140 );
//        getDataFromIni( &(m_sdlRect->y), "whitePawn", "iPositionY", 140 );
//        getDataFromIni( &(m_sdlRect->w), "whitePawn", "iWidth", 40 );
//        getDataFromIni( &(m_sdlRect->h), "whitePawn", "iHeight", 40 );
//        if( m_fIsVisible ) { m_gameWindow->addObjectForRenderer( this ); }
//    }
//    else
//    {
//        setToLog( "WhitePawn texture didn't create." );
//    }
//}


// ----------------------------------------------------------------------------
TextBox::~TextBox()
{
    m_gameWindow->deleteObjectFromRenderer( this );
}



// ----------------------------------------------------------------------------