#include "ChessLMV.h"



// ----------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    setToLog( "Start program." );
    
    GameWindow gameWindow;
    if( !( gameWindow.m_fIsSuccess ) )
    {
        setToLog( "Cannot create window." );
        return 1;
    }

    Background *pBackground = nullptr;
    ChessBoard *pChessBoard = nullptr;
    TextMenu *pTextMenu = nullptr;

    prepareElements( &gameWindow, &pBackground, &pChessBoard, &pTextMenu );
    gameWindow.refresh();

    while( gameWindow.m_fIsSuccess )
    {
        pushPosition( &gameWindow, &pBackground, &pChessBoard, &pTextMenu );
        gameWindow.refresh();
    }

    delElements( &pBackground, &pChessBoard, &pTextMenu );
    setToLog( "End program.\n\n" );
    //getchar();
    return 0;
}



// ----------------------------------------------------------------------------
bool prepareElements( GameWindow *pGameWindow, Background **ppBackground,
        ChessBoard **ppChessBoard, TextMenu **ppTextMenu )
{

    *ppBackground = new Background( pGameWindow );
    if( !( pGameWindow->m_fIsSuccess ) )
    {
        setToLog( "Cannot create background." );
        return false;
    }

    *ppChessBoard = new ChessBoard( pGameWindow );
    if( !( pGameWindow->m_fIsSuccess ) )
    {
        setToLog( "Cannot create chess board." );
        return false;
    }

    *ppTextMenu = new TextMenu( pGameWindow );
    return true;
}



// ----------------------------------------------------------------------------
void delElements( Background **ppBackground, ChessBoard **ppChessBoard,
        TextMenu **ppTextMenu )
{
    if( *ppTextMenu != nullptr ) { delete *ppTextMenu; }
    if( *ppChessBoard != nullptr ) { delete *ppChessBoard; }
    if( *ppBackground != nullptr ) { delete *ppBackground; }
}



// ----------------------------------------------------------------------------
void pushPosition( GameWindow *pGameWindow, Background **ppBackground,
        ChessBoard **ppChessBoard, TextMenu **ppTextMenu )
{
    SDL_Event sdlEvent;
    while( true )
    {
        SDL_WaitEvent( &sdlEvent );
        switch( sdlEvent.type )
        {
            case SDL_QUIT:
            {
                setToLog( "Push to exit game." );
                pGameWindow->m_fIsSuccess = false;
                return; // break;
            }
            case SDL_MOUSEBUTTONDOWN:
            {
                IntPoint pushPosition = IntPoint( sdlEvent.button.x,
                        sdlEvent.button.y );

                // Check push board.
                if( checkPushPlace( *ppChessBoard, pushPosition ) )
                {
                    (*ppChessBoard)->pushAnalysis( IntPoint( sdlEvent.button.x,
                            sdlEvent.button.y ) );
                    return; // break;
                }

                // ------------------------------------------------------------
                // Check push menu.
                if( checkPushPlace( *ppTextMenu, pushPosition ) )
                {
                    int iResultAnalysis = (*ppTextMenu)->pushAnalysis(
                            IntPoint( sdlEvent.button.x, sdlEvent.button.y ) );
                    switch( iResultAnalysis )
                    {
                        case _NO_COMMAND_:
                        {
                            (*ppChessBoard)->boardPause();
                            break;
                        }
                        case _NEW_GAME_:
                        {
                            setToLog( "Push new game." );
                            delElements( ppBackground, ppChessBoard,
                                    ppTextMenu );
                            prepareElements( pGameWindow, ppBackground,
                                    ppChessBoard, ppTextMenu );
                            break;
                        }
                        case _DRAW_:
                        {
                            setToLog( "Push draw." );
                            (*ppChessBoard)->toHelp( std::string( "The " ) +
                                    "game is over. Please choose next action" +
                                    " - new game or exit." );
                            (*ppTextMenu)->getTextDraw()->changeVisible();
                            (*ppTextMenu)->getTextCapitulation()->
                                    changeVisible();
                            (*ppChessBoard)->gameOver( _GO_DRAW_ );
                            break;
                        }
                        case _CAPITULATION_:
                        {
                            setToLog( "Push capitulation." );
                            (*ppChessBoard)->toHelp( std::string( "The " ) +
                                    "game is over. Please choose next action" +
                                    " - new game or exit." );
                            (*ppTextMenu)->getTextDraw()->changeVisible();
                            (*ppTextMenu)->getTextCapitulation()->
                                    changeVisible();
                            (*ppChessBoard)->gameOver( _GO_CAPITULATION_ );

                            break;
                        }
                        case _EXIT_:
                        {
                            setToLog( "Push to exit game." );
                            pGameWindow->m_fIsSuccess = false;
                            break;
                        }
                    }
                    return; // break;
                }
                break;
            }
        }
    }
}



// ----------------------------------------------------------------------------
bool checkPushPlace( GameObject *pSpace, IntPoint pushPosition )
{
    IntPoint buffPosition = pSpace->getPosition();
    IntPoint buffSize = pSpace->getSize();

    return ( ( pushPosition.x >= buffPosition.x ) && (
            pushPosition.x <= buffPosition.x + buffSize.x ) && (
            pushPosition.y >= buffPosition.y ) && (
            pushPosition.y <= buffPosition.y + buffSize.y ) );
}