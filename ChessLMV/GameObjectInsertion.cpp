#include "GameObjectInsertion.h"


// ----------------------------------------------------------------------------
GameObjectInsertion::GameObjectInsertion(
        GameWindow *inputGameWindow /*= nullptr*/,
        SDL_Texture *inputTexture /*= nullptr*/, int iPositionX /*= 0*/,
        int iPositionY /*= 0*/, int iWidth /*= 0*/, int iHeight /*= 0*/ ) :
                GameObject( inputTexture, iPositionX, iPositionY,
                        iWidth, iHeight )
{
    m_gameWindow = inputGameWindow;
}



// ----------------------------------------------------------------------------