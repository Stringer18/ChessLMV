#include "TextMenu.h"


// ----------------------------------------------------------------------------
TextMenu::TextMenu( GameWindow *pGameWindow ) :
        GameObjectInsertion( pGameWindow )
{
    iCommandStore = _NO_COMMAND_;

    int iButtonPositionX = 0;
    int iButtonPositionY = 0;
    int iButtonWidthSize = 0;
    int iButtonStep = 0;

    getDataFromIni( &iButtonPositionX, "buttonMenu", "iPositionX", 600 );
    getDataFromIni( &iButtonPositionY, "buttonMenu", "iPositionY", 450 );
    getDataFromIni( &iButtonWidthSize, "buttonMenu", "iWidthSize", 100 );
    getDataFromIni( &iButtonStep, "buttonMenu", "iStep", 10 );

    m_sdlRect->x = iButtonPositionX;
    m_sdlRect->y = iButtonPositionY;
    m_sdlRect->w = 0;
    m_sdlRect->h = 0;

    // ------------------------------------------------------------------------
    pTextNewGame = new TextBox( pGameWindow, "New Game", IntPoint(
            iButtonPositionX, iButtonPositionY ), iButtonWidthSize, true );
    m_sdlRect->w += pTextNewGame->getSize().x;
    
    // ------------------------------------------------------------------------
    iButtonPositionY += pTextNewGame->getSize().y + iButtonStep;
    pTextExit = new TextBox( pGameWindow, "Exit", IntPoint(
            iButtonPositionX, iButtonPositionY ), iButtonWidthSize, true );
    if( m_sdlRect->w < pTextExit->getSize().x )
    {
        m_sdlRect->w = pTextExit->getSize().x;
    }

    // ------------------------------------------------------------------------
    iButtonPositionY += pTextExit->getSize().y + iButtonStep;
    pTextYes = new TextBox( pGameWindow, "Yes", IntPoint(
            iButtonPositionX, iButtonPositionY ), iButtonWidthSize, false );

    iButtonPositionX += pTextYes->getSize().x + iButtonStep;
    pTextNo = new TextBox( pGameWindow, "No", IntPoint(
            iButtonPositionX, iButtonPositionY ), iButtonWidthSize, false );

    // ------------------------------------------------------------------------
    // Calculating size of menu
    if( m_sdlRect->w < ( pTextYes->getSize().x + iButtonStep +
            pTextNo->getSize().x ) )
    {
        m_sdlRect->w = pTextYes->getSize().x + iButtonStep +
                pTextNo->getSize().x;
    }
    m_sdlRect->h = iButtonPositionY - pTextNewGame->getPosition().y +
            ( ( pTextYes->getSize().y > pTextNo->getSize().y ) ?
            pTextYes->getSize().y : pTextNo->getSize().y );
}



// ----------------------------------------------------------------------------
TextMenu::~TextMenu()
{
    if( pTextNewGame != nullptr ) { delete pTextNewGame; }
    if( pTextExit != nullptr ) { delete pTextExit; }
    if( pTextYes != nullptr ) { delete pTextYes; }
    if( pTextNo != nullptr ) { delete pTextNo; }
}



// ----------------------------------------------------------------------------
int TextMenu::pushAnalysis( IntPoint pushPoint )
{
    if( pTextYes->getIsVisible() )
    {
        if( checkPushButton( pTextYes, pushPoint ) )
        {
            int ibuffCommand = iCommandStore;
            iCommandStore = _NO_COMMAND_;
            pTextYes->changeVisible();
            pTextNo->changeVisible();
            return ibuffCommand;
        }
        if( checkPushButton( pTextNo, pushPoint ) )
        {
            iCommandStore = _NO_COMMAND_;
            if( !( pTextNewGame->getIsVisible() ) )
            {
                pTextNewGame->changeVisible();
            }
            if( !( pTextExit->getIsVisible() ) )
            {
                pTextExit->changeVisible();
            }
            pTextYes->changeVisible();
            pTextNo->changeVisible();
            return _NO_COMMAND_;
        }
    }
    else
    {
        if( checkPushButton( pTextNewGame, pushPoint ) )
        {
            iCommandStore = _NEW_GAME_;
            pTextExit->changeVisible();
            pTextYes->changeVisible();
            pTextNo->changeVisible();
            return _NO_COMMAND_;
        }
        if( checkPushButton( pTextExit, pushPoint ) )
        {
            iCommandStore = _EXIT_;
            pTextNewGame->changeVisible();
            pTextYes->changeVisible();
            pTextNo->changeVisible();
            return _NO_COMMAND_;
        }
    }
    return _NO_COMMAND_;
}



// ----------------------------------------------------------------------------
bool TextMenu::checkPushButton( TextBox *pButton, IntPoint pushPosition )
{
    IntPoint buffPosition = pButton->getPosition();
    IntPoint buffSize = pButton->getSize();

    return ( ( pushPosition.x >= buffPosition.x ) && (
            pushPosition.x <= buffPosition.x + buffSize.x ) && (
            pushPosition.y >= buffPosition.y ) && (
            pushPosition.y <= buffPosition.y + buffSize.y ) && (
            pButton->getIsVisible() ) );
}



// ----------------------------------------------------------------------------