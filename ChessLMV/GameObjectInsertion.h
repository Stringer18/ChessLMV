#pragma once

#include "GameObject.h"
#include "GameWindow.h"

// This insertion-class is designed for a single mission - to avoid
// cross-inclusion between GameWindow and other classes. This is due to the
// need to add an array of objects (m_pRefreshElements) to the GameWindow that
// need to be rendered.
// ----------------------------------------------------------------------------
class GameObjectInsertion : public GameObject
{
    public:
        GameObjectInsertion( GameWindow *inputGameWindow = nullptr,
                SDL_Texture *inputTexture = nullptr,
                int iPositionX = 0, int iPositionY = 0,
                int iWidth = 0, int iHeight = 0 );


        
    // ------------------------------------------------------------------------
    protected:
        GameWindow *m_gameWindow;
};



// ----------------------------------------------------------------------------