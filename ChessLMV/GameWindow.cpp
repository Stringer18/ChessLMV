#include "GameWindow.h"


// ----------------------------------------------------------------------------
GameWindow::GameWindow()
{
    getDataFromIni( &m_iPositionX, "gameWindow", "iPositionX", 100 );
    getDataFromIni( &m_iPositionY, "gameWindow", "iPositionY", 100 );
    getDataFromIni( &m_iWidth, "gameWindow", "iWidth", 800 );
    getDataFromIni( &m_iHeight, "gameWindow", "iHeight", 600 );

    m_fIsSuccess = initSdlComponents();
}



// ----------------------------------------------------------------------------
GameWindow::~GameWindow()
{
    m_pvectRefreshElements.clear();
    if( m_sdlRenderer != nullptr ) { SDL_DestroyRenderer( m_sdlRenderer ); }
	if( m_sdlGameWindow != nullptr ) { SDL_DestroyWindow( m_sdlGameWindow ); }
    //TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}



// ----------------------------------------------------------------------------
bool GameWindow::initSdlComponents()
{
    // SDL
    if ( SDL_Init( SDL_INIT_EVERYTHING ) != 0 )
    {
        setToLog( std::string( "SDL_Init Error: ") + SDL_GetError() );
        return false;
    }
    
    // Image (png)
    int iflags = IMG_INIT_PNG;
    if ( !( IMG_Init( iflags ) & iflags ) )
    {
        setToLog( std::string( "Can't init image: " ) + IMG_GetError() );
        return false;
    }

    // Window
    m_sdlGameWindow = SDL_CreateWindow( "Chess", m_iPositionX, m_iPositionY,
            m_iWidth, m_iHeight, SDL_WINDOW_SHOWN );
    if ( m_sdlGameWindow == nullptr )
    {
        setToLog( std::string( "SDL_CreateWindow Error: " ) +
                SDL_GetError() );
        return false;
    }

    // Renderer
    m_sdlRenderer = SDL_CreateRenderer( m_sdlGameWindow, -1,
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    if ( m_sdlRenderer == nullptr )
    {
        setToLog( std::string( "SDL_CreateRenderer Error: " ) +
                SDL_GetError() );
        return false;
    }


    //if( m_fIsSuccess )
    //{
    //    if ( TTF_Init() != 0 )
    //    {
    //        printf( "TTF_Init Error.\n" );
    //        m_fIsSuccess = false;
    //    }
    //    //else
    //    //{}
    return true;
}



// ----------------------------------------------------------------------------
bool GameWindow::strPngTextureToSdlTexture( SDL_Texture*& sdlResultTexture,
        std::string strPngTexture )
{
    if ( sdlResultTexture != nullptr )
    {
        setToLog( "Texture is not empty." );
        return false;
    }
    SDL_Surface* sdlBuffSurfacePng = IMG_Load( strPngTexture.c_str() );
    if ( sdlBuffSurfacePng == nullptr )
    {	
        setToLog( std::string( "IMG_Load Error: " ) + IMG_GetError() );
        return false;
    }
    sdlResultTexture = SDL_CreateTextureFromSurface( m_sdlRenderer,
            sdlBuffSurfacePng );
    SDL_FreeSurface( sdlBuffSurfacePng );
    return true;
}



// ----------------------------------------------------------------------------
int GameWindow::addObjectForRenderer( GameObject *pGameObject )
{
    for( unsigned int i = 0 ; i < m_pvectRefreshElements.size() ; i++ )
    {
        if( m_pvectRefreshElements[i] == pGameObject )
        {
            return i;
        }
    }
    m_pvectRefreshElements.push_back( pGameObject );
    return ( m_pvectRefreshElements.size() - 1 );
}



// ----------------------------------------------------------------------------
void GameWindow::deleteObjectFromRenderer( GameObject *pGameObject )
{
    for( unsigned int i = 0 ; i < m_pvectRefreshElements.size() ; i++ )
    {
        if( m_pvectRefreshElements[i] == pGameObject )
        {
            m_pvectRefreshElements.erase( m_pvectRefreshElements.begin() + i );
            return;
        }
    }
}



// ----------------------------------------------------------------------------
void GameWindow::refresh()
{
    SDL_RenderClear( m_sdlRenderer );

    for( unsigned int i = 0 ; i < m_pvectRefreshElements.size() ; i++ )
    {
        SDL_RenderCopy( m_sdlRenderer, m_pvectRefreshElements[i]->getTexture(),
                NULL, m_pvectRefreshElements[i]->getRect() );
    }
        
    SDL_RenderPresent( m_sdlRenderer );
}



// ----------------------------------------------------------------------------