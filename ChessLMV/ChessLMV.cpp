#include "ChessLMV.h"



// ----------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    setToLog( "Start program." );
    
    GameWindow gameWindow;
    Background *background = new Background( &gameWindow );
    ChessBoard *chessBoard = new ChessBoard( &gameWindow );
    
    gameWindow.refresh();

    SDL_Delay(2000);

    delete chessBoard;
    delete background;
    gameWindow.refresh();
    SDL_Delay(2000);

    setToLog( "Exit.\n\n" );
    getchar();
    return 0;
}



// ----------------------------------------------------------------------------