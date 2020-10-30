#include "TextMenu.h"


// ----------------------------------------------------------------------------
TextMenu::TextMenu( GameWindow *pGameWindow ) :
        GameObjectInsertion( pGameWindow )
{
    m_iCommandStore = _NO_COMMAND_;
    m_fIsNewGameOrExitMode = false;

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
    pTextDraw = new TextBox( pGameWindow, "Draw", IntPoint(
            iButtonPositionX, iButtonPositionY ), iButtonWidthSize, true );
    if( m_sdlRect->w < pTextDraw->getSize().x )
    {
        m_sdlRect->w = pTextDraw->getSize().x;
    }

    // ------------------------------------------------------------------------
    iButtonPositionY += pTextNewGame->getSize().y + iButtonStep;
    pTextCapitulation = new TextBox( pGameWindow, "Capitulation", IntPoint(
            iButtonPositionX, iButtonPositionY ), iButtonWidthSize, true );
    if( m_sdlRect->w < pTextCapitulation->getSize().x )
    {
        m_sdlRect->w = pTextCapitulation->getSize().x;
    }

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
    if( pTextDraw != nullptr ) { delete pTextDraw; }
    if( pTextCapitulation != nullptr ) { delete pTextCapitulation; }
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
            int ibuffCommand = m_iCommandStore;
            m_iCommandStore = _NO_COMMAND_;
            if( m_fIsNewGameOrExitMode ) { NewGameOrExitMode(); }
            else { returnMenu(); }
            return ibuffCommand;
        }
        if( checkPushButton( pTextNo, pushPoint ) )
        {
            m_iCommandStore = _NO_COMMAND_;
            if( m_fIsNewGameOrExitMode ) { NewGameOrExitMode(); }
            else { returnMenu(); }
            return _NO_COMMAND_;
        }
    }
    else
    {
        if( checkPushButton( pTextNewGame, pushPoint ) )
        {
            confirmation( _NEW_GAME_ );
            return _NO_COMMAND_;
        }
        if( checkPushButton( pTextDraw, pushPoint ) )
        {
            confirmation( _DRAW_ );
            return _NO_COMMAND_;
        }
        if( checkPushButton( pTextCapitulation, pushPoint ) )
        {
            confirmation( _CAPITULATION_ );
            return _NO_COMMAND_;
        }
        if( checkPushButton( pTextExit, pushPoint ) )
        {
            confirmation( _EXIT_ );
            return _NO_COMMAND_;
        }
    }
    return _NO_COMMAND_;
}



// ----------------------------------------------------------------------------
void TextMenu::hideMenu()
{
    if( pTextNewGame->getIsVisible() ) { pTextNewGame->changeVisible(); }
    if( pTextDraw->getIsVisible() ) { pTextDraw->changeVisible(); }
    if( pTextCapitulation->getIsVisible() )
            { pTextCapitulation->changeVisible(); }
    if( pTextExit->getIsVisible() ) { pTextExit->changeVisible(); }
    if( pTextYes->getIsVisible() ) { pTextYes->changeVisible(); }
    if( pTextNo->getIsVisible() ) { pTextNo->changeVisible(); }
}



// ----------------------------------------------------------------------------
void TextMenu::returnMenu()
{
    if( !pTextNewGame->getIsVisible() ) { pTextNewGame->changeVisible(); }
    if( !pTextDraw->getIsVisible() ) { pTextDraw->changeVisible(); }
    if( !pTextCapitulation->getIsVisible() )
            { pTextCapitulation->changeVisible(); }
    if( !pTextExit->getIsVisible() ) { pTextExit->changeVisible(); }
    if( pTextYes->getIsVisible() ) { pTextYes->changeVisible(); }
    if( pTextNo->getIsVisible() ) { pTextNo->changeVisible(); }
}




// ----------------------------------------------------------------------------
void TextMenu::NewGameOrExitMode()
{
    m_fIsNewGameOrExitMode = true;
    if( !pTextNewGame->getIsVisible() ) { pTextNewGame->changeVisible(); }
    if( pTextDraw->getIsVisible() ) { pTextDraw->changeVisible(); }
    if( pTextCapitulation->getIsVisible() )
            { pTextCapitulation->changeVisible(); }
    if( !pTextExit->getIsVisible() ) { pTextExit->changeVisible(); }
    if( pTextYes->getIsVisible() ) { pTextYes->changeVisible(); }
    if( pTextNo->getIsVisible() ) { pTextNo->changeVisible(); }
}



// ----------------------------------------------------------------------------
bool TextMenu::checkPushButton( TextBox *pButton, IntPoint pushPoint )
{
    IntPoint buffPoint = pButton->getPosition();
    IntPoint buffSize = pButton->getSize();

    return ( ( pButton->getIsVisible() ) && (
            pushPoint.x >= buffPoint.x ) && (
            pushPoint.x <= buffPoint.x + buffSize.x ) && (
            pushPoint.y >= buffPoint.y ) && (
            pushPoint.y <= buffPoint.y + buffSize.y ) );
}



// ----------------------------------------------------------------------------
void TextMenu::confirmation( int iVisibleButton )
{
    if( ( iVisibleButton <= _NO_COMMAND_ ) ||
            ( iVisibleButton >= _COMMAND_TEXT_MENU_MAX_ ) )
    {
        return;
    }
    m_iCommandStore = iVisibleButton;
    hideMenu();
    switch( iVisibleButton )
    {
        case _NEW_GAME_:
        {
            if( !pTextNewGame->getIsVisible() ) 
            {
                pTextNewGame->changeVisible();
            }
            break;
        }
        case _DRAW_:
        {
            if( !pTextDraw->getIsVisible() ) 
            {
                pTextDraw->changeVisible();
            }
            break;
        }
        case _CAPITULATION_:
        {
            if( !pTextCapitulation->getIsVisible() ) 
            {
                pTextCapitulation->changeVisible();
            }
            break;
        }
        case _EXIT_:
        {
            if( !pTextExit->getIsVisible() ) 
            {
                pTextExit->changeVisible();
            }
            break;
        }
    }
    if( !pTextYes->getIsVisible() ) { pTextYes->changeVisible(); }
    if( !pTextNo->getIsVisible() ) { pTextNo->changeVisible(); }
}



// ----------------------------------------------------------------------------