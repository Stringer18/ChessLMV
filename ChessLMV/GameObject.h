#pragma once

#include <SDL.h>

#include "IntPoint.h"

// ----------------------------------------------------------------------------
class GameObject
{
    public:
        GameObject( SDL_Texture *inputTexture = nullptr, int iPositionX = 0,
                int iPositionY = 0, int iWidth = 0, int iHeight = 0 );
        ~GameObject();

        IntPoint getSize() const;
        IntPoint getPosition() const;
        SDL_Rect* getRect() const;
        SDL_Texture* getTexture() const;


        void setPosition( const IntPoint position );
        void setPosition( int iX, int iY );
        
        // An instance is valid if it's texture is not nullptr.
        bool isValid();

    // ------------------------------------------------------------------------
    protected:
        SDL_Texture* m_sdlTexture;
        SDL_Rect* m_sdlRect;
};
// ----------------------------------------------------------------------------