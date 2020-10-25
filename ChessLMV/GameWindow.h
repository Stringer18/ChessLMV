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
        // Turns message into texture (sdlResultTexture). It return true if 
        // everything is successful.
        // If you give a pointer to a non-nullptr texture,
        // then nothing will happen and the function will return false. 
        bool strTextToSdlTexture( SDL_Texture*& sdlResultTexture,
                std::string strMessage, Uint32 uiWidthSize, int iFontSize = -1,
                SDL_Color *psdlColor = nullptr );


        // --------------------------------------------------------------------
        // Add object to end of m_vectpRefreshElements (if it not in).
        // Return index.
        int addObjectForRenderer( GameObject *pGameObject );


        // --------------------------------------------------------------------
        // Delete object from m_vectpRefreshElements.
        void deleteObjectFromRenderer( GameObject *pGameObject );


        // --------------------------------------------------------------------
        // The function updates the picture.
        void refresh();


        // --------------------------------------------------------------------
        // Function for checking and correct conversion of int to uint8.
        bool intToUint8( Uint8 *uint8Result, int iNumber );


        // --------------------------------------------------------------------
        // This flag is in case an error occurs while creating an object.
        // If it false, we correctly break all and destroy objects, which were
        // created earlier.
        bool m_fIsSuccess;


    // ------------------------------------------------------------------------
    protected:
        // Load data from ini-file for further work with the font.
        void prepareFont();


        // --------------------------------------------------------------------
        SDL_Window* m_sdlGameWindow;
        SDL_Renderer* m_sdlRenderer;

        int m_iPositionX;
        int m_iPositionY;
        int m_iWidth;
        int m_iHeight;

        // This vector stores pointers to all objects that need to be render.
        std::vector<GameObject*> m_vectpRefreshElements;

        int m_iDefaultFontSize;
        SDL_Color m_sdlDefaultFontColor;
        std::string m_strFontFile;

    // ------------------------------------------------------------------------
    private:
        // Initializing SDL (in general), image, window, render, font.
        bool initSdlComponents();

};