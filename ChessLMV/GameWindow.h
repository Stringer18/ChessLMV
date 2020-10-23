#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <vector>

#include "HelpFunctions.hpp"
#include "GameObject.h"


// ----------------------------------------------------------------------------
class GameWindow
{
    // ------------------------------------------------------------------------
    public:
        GameWindow();
        ~GameWindow();

        // --------------------------------------------------------------------
        // Turns the path to the png-file (strPngTexture) into texture
        // (sdlResultTexture). It return true if everything is successful.
        // If you give a pointer to a non-nullptr texture,
        // then nothing will happen and the function will return false. 
        bool strPngTextureToSdlTexture( SDL_Texture*& sdlResultTexture,
                std::string strPngTexture );


        // --------------------------------------------------------------------
        // Add object to end of m_pvectRefreshElements (if it not in).
        // Return index.
        int addObjectForRenderer( GameObject *pGameObject );


        // --------------------------------------------------------------------
        // Delete object from m_pvectRefreshElements.
        void deleteObjectFromRenderer( GameObject *pGameObject );


        // --------------------------------------------------------------------
        // The function updates the picture.
        void refresh();


        // --------------------------------------------------------------------
        // This flag is in case an error occurs while creating an object.
        // If it false, we correctly break all and destroy objects, which were
        // created earlier.
        bool m_fIsSuccess;


    // ------------------------------------------------------------------------
    protected:
        SDL_Window* m_sdlGameWindow;
        SDL_Renderer* m_sdlRenderer;

        int m_iPositionX;
        int m_iPositionY;
        int m_iWidth;
        int m_iHeight;

        // An array of objects for rendering. and the index of the first free
        // cell (so as not to search for it every time).
        std::vector<GameObject*> m_pvectRefreshElements;

    // ------------------------------------------------------------------------
    private:
        // Initializing SDL (in general), window, render font.
        bool initSdlComponents();

};