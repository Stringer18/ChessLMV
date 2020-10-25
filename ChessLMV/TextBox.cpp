#include "TextBox.h"

// ----------------------------------------------------------------------------
TextBox::TextBox( GameWindow *inputGameWindow, std::string strMessage,
        IntPoint position, Uint32 uiWidthSize, bool fIsVisible /*= false*/,
        int iFontSize /*= -1*/, SDL_Color *sdlColor /*= nullptr*/ ) :
                GameObjectInsertion( inputGameWindow )
{
    m_fIsVisible = fIsVisible;

    m_gameWindow->m_fIsSuccess = m_gameWindow->strTextToSdlTexture(
            m_sdlTexture, strMessage, uiWidthSize, iFontSize, sdlColor );

    if( m_gameWindow->m_fIsSuccess )
    {
        setPosition( position );
        SDL_QueryTexture( m_sdlTexture, NULL, NULL, &(m_sdlRect->w),
                &(m_sdlRect->h) );
        if( m_fIsVisible ) { m_gameWindow->addObjectForRenderer( this ); }
    }
    else
    {
        setToLog( "TextBox texture didn't create." );
    }
}


// ----------------------------------------------------------------------------
TextBox::~TextBox()
{
    if( m_fIsVisible ) { m_gameWindow->deleteObjectFromRenderer( this ); }
}



// ----------------------------------------------------------------------------
void TextBox::changeVisible()
{
    m_fIsVisible = !(m_fIsVisible);
    if( m_fIsVisible ) { m_gameWindow->addObjectForRenderer( this ); }
    else { m_gameWindow->deleteObjectFromRenderer( this ); }
}



// ----------------------------------------------------------------------------
bool TextBox::getIsVisible() { return m_fIsVisible; }



// ----------------------------------------------------------------------------