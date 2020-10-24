#include "GameWindow.h"


// ----------------------------------------------------------------------------
GameWindow::GameWindow()
{
    getDataFromIni( &m_iPositionX, "gameWindow", "iPositionX", 100 );
    getDataFromIni( &m_iPositionY, "gameWindow", "iPositionY", 100 );
    getDataFromIni( &m_iWidth, "gameWindow", "iWidth", 800 );
    getDataFromIni( &m_iHeight, "gameWindow", "iHeight", 600 );

    m_fIsSuccess = initSdlComponents();

    if( m_fIsSuccess ) { prepareFont(); }
}



// ----------------------------------------------------------------------------
GameWindow::~GameWindow()
{
    m_pvectRefreshElements.clear();
    if( m_sdlRenderer != nullptr ) { SDL_DestroyRenderer( m_sdlRenderer ); }
	if( m_sdlGameWindow != nullptr ) { SDL_DestroyWindow( m_sdlGameWindow ); }
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}



// ----------------------------------------------------------------------------
bool GameWindow::initSdlComponents()
{
    // SDL
    if( SDL_Init( SDL_INIT_EVERYTHING ) != 0 )
    {
        setToLog( std::string( "SDL_Init Error: ") + SDL_GetError() );
        return false;
    }
    
    // Image (png)
    int iflags = IMG_INIT_PNG;
    if( !( IMG_Init( iflags ) & iflags ) )
    {
        setToLog( std::string( "Can't init image: " ) + IMG_GetError() );
        return false;
    }

    // Window
    m_sdlGameWindow = SDL_CreateWindow( "Chess", m_iPositionX, m_iPositionY,
            m_iWidth, m_iHeight, SDL_WINDOW_SHOWN );
    if( m_sdlGameWindow == nullptr )
    {
        setToLog( std::string( "SDL_CreateWindow Error: " ) + SDL_GetError() );
        return false;
    }

    // Renderer
    m_sdlRenderer = SDL_CreateRenderer( m_sdlGameWindow, -1,
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    if( m_sdlRenderer == nullptr )
    {
        setToLog( std::string( "SDL_CreateRenderer Error: " ) +
                SDL_GetError() );
        return false;
    }

    // Font
    if( TTF_Init() != 0 )
    {
        setToLog( std::string( "TTF_Init Error: " ) + SDL_GetError() );
        return false;
    }

    return true;
}



// ----------------------------------------------------------------------------
bool GameWindow::strPngTextureToSdlTexture( SDL_Texture*& sdlResultTexture,
        std::string strPngTexture )
{
    if( sdlResultTexture != nullptr )
    {
        setToLog( "Texture is not empty." );
        return false;
    }

    SDL_Surface* sdlBuffSurface = IMG_Load( strPngTexture.c_str() );
    if( sdlBuffSurface == nullptr )
    {	
        setToLog( std::string( "IMG_Load Error: " ) + IMG_GetError() );
        return false;
    }
    sdlResultTexture = SDL_CreateTextureFromSurface( m_sdlRenderer,
            sdlBuffSurface );
    SDL_FreeSurface( sdlBuffSurface );
    return true;
}



// ----------------------------------------------------------------------------
bool GameWindow::strTextToSdlTexture( SDL_Texture*& sdlResultTexture,
                std::string strMessage, int iFontSize /*= -1*/,
                SDL_Color *psdlColor /*= nullptr*/ )
{
    if( sdlResultTexture != nullptr )
    {
        setToLog( "Texture is not empty." );
        return false;
    }
    if( iFontSize < 1 ) { iFontSize = m_iDefaultFontSize; }
    if( psdlColor == nullptr ) { psdlColor = &m_sdlDefaultFontColor; }

    TTF_Font *pFont = TTF_OpenFont( m_strFontFile.c_str(), iFontSize );
    if( pFont == nullptr )
    {
        setToLog( std::string( "TTF_OpenFont Error: " ) + SDL_GetError() );
        return false;
    }

    SDL_Surface *sdlBuffSurface = TTF_RenderText_Blended( pFont,
            strMessage.c_str(), *psdlColor);
    if( sdlBuffSurface == nullptr )
    {
        TTF_CloseFont( pFont );
        setToLog( std::string( "TTF_RenderText Error: " ) + SDL_GetError() );
        return false;
    }
    sdlResultTexture = SDL_CreateTextureFromSurface( m_sdlRenderer,
            sdlBuffSurface );
    if( sdlResultTexture == nullptr )
    {
        setToLog( std::string( "CreateTexture Error: " ) + SDL_GetError() );
        return false;
    }

    SDL_FreeSurface( sdlBuffSurface );
    TTF_CloseFont( pFont );
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
bool GameWindow::intToUint8( Uint8 *uint8Result, int iNumber )
{
    if( uint8Result == nullptr )
    {
        setToLog( "Error: Empty pointer Uint8 *uint8Result." );
        return false;
    }
    if( iNumber < 0 )
    {
        *uint8Result = 0;
        return false;
    }
    if( iNumber > 255 )
    {
        *uint8Result = 255;
        return false;
    }
    *uint8Result = (Uint8) iNumber;
    return true;
}



// ----------------------------------------------------------------------------
int GameWindow::getDefaultFontSize() { return m_iDefaultFontSize; }
SDL_Color GameWindow::getDefaultFontColor() { return m_sdlDefaultFontColor; }



// ----------------------------------------------------------------------------
void GameWindow::prepareFont()
{
    getDataFromIni( &m_iDefaultFontSize, "font", "iDefaultSize", 12 );
    
    int iBuff = 0;

    getDataFromIni( &iBuff, "font", "isdlDefaultColorR", 255 );
    if( !( intToUint8( &(m_sdlDefaultFontColor.r), iBuff ) ) )
    { setToLog( "Invalid value for sdlDefaultFontColor->r. Rounded." ); }

    getDataFromIni( &iBuff, "font", "isdlDefaultColorG", 255 );
    if( !( intToUint8( &(m_sdlDefaultFontColor.g), iBuff ) ) )
    { setToLog( "Invalid value for sdlDefaultFontColor->g. Rounded." ); }

    getDataFromIni( &iBuff, "font", "isdlDefaultColorB", 255 );
    if( !( intToUint8( &(m_sdlDefaultFontColor.b), iBuff ) ) )
    { setToLog( "Invalid value for sdlDefaultFontColor->b. Rounded." ); }

    getDataFromIni( &iBuff, "font", "isdlDefaultColorA", 255 );
    if( !( intToUint8( &(m_sdlDefaultFontColor.a), iBuff ) ) )
    { setToLog( "Invalid value for sdlDefaultFontColor->a. Rounded." ); }

    getDataFromIni( m_strFontFile, "font", "strFont",
            ".\\Resources\\OldStandardTTItalic.ttf" );
}



// ----------------------------------------------------------------------------