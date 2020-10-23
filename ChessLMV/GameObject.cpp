#include "GameObject.h"

// ----------------------------------------------------------------------------
GameObject::GameObject( SDL_Texture *inputTexture /*= nullptr*/,
        int iPositionX /*= 0*/, int iPositionY /*= 0*/,
        int iWidth /*= 0*/, int iHeight /*= 0*/)
{
    m_sdlTexture = inputTexture;
    m_sdlRect = new SDL_Rect();
    m_sdlRect->x = iPositionX;
    m_sdlRect->y = iPositionY;
    m_sdlRect->w = iWidth;
    m_sdlRect->h = iHeight;
}


// ----------------------------------------------------------------------------
GameObject::~GameObject()
{
    if( m_sdlRect != nullptr ) { delete m_sdlRect; }
}


// ----------------------------------------------------------------------------
IntPoint GameObject::getSize() const
{
    return IntPoint( m_sdlRect->w, m_sdlRect->h );
}


// ----------------------------------------------------------------------------
IntPoint GameObject::getPosition() const
{
    return IntPoint( m_sdlRect->x, m_sdlRect->y );
}


// ----------------------------------------------------------------------------
SDL_Rect* GameObject::getRect() const { return m_sdlRect; }


// ----------------------------------------------------------------------------
SDL_Texture* GameObject::getTexture() const { return m_sdlTexture; }



// ----------------------------------------------------------------------------
void GameObject::setPosition( const IntPoint position )
{
    m_sdlRect->x = position.x;
    m_sdlRect->y = position.y;
}

void GameObject::setPosition( int iX, int iY )
{
    m_sdlRect->x = iX;
    m_sdlRect->y = iY;
}


// ----------------------------------------------------------------------------
bool GameObject::isValid() { return ( m_sdlTexture != nullptr ); }



// ----------------------------------------------------------------------------