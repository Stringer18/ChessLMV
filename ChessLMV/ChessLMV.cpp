#include "ChessLMV.h"



// ----------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    setToLog( "Start program." );
    
    GameWindow gameWindow;
    Background *background = new Background( &gameWindow );

    gameWindow.refresh();
    SDL_Delay(2000);

    ChessBoard *chessBoard = new ChessBoard( &gameWindow );

    gameWindow.refresh();
    SDL_Delay(2000);

    TextBox * textBox = new TextBox( &gameWindow, "Test Message.",
            IntPoint( 80, 120 ), true );

    gameWindow.refresh();
    SDL_Delay(2000);

    delete textBox;

    gameWindow.refresh();
    SDL_Delay(2000);

    delete chessBoard;

    gameWindow.refresh();
    SDL_Delay(2000);

    delete background;

    gameWindow.refresh();
    SDL_Delay(2000);

    setToLog( "Exit.\n\n" );
    getchar();
    return 0;
}



// ----------------------------------------------------------------------------