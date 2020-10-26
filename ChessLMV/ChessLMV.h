#pragma once

#include <vector>

#include "HelpFunctions.hpp"
#include "GameWindow.h"
#include "GameObject.h"
#include "Background.h"
#include "ChessBoard.h"
#include "TextMenu.h"


// ----------------------------------------------------------------------------
// Create elements before start of game.
bool prepareElements( GameWindow *pGameWindow, Background **ppBackground,
        ChessBoard **ppChessBoard, TextMenu **ppTextMenu );


// ----------------------------------------------------------------------------
// Delete elements before exit from of game.
void delElements( Background **ppBackground, ChessBoard **ppChessBoard,
        TextMenu **ppTextMenu );


// ----------------------------------------------------------------------------
// Reads button presses and analysis it. Decides what action to take as a
// result of this click.
void pushPosition( GameWindow *pGameWindow, Background **ppBackground,
        ChessBoard **ppChessBoard, TextMenu **ppTextMenu );


// ----------------------------------------------------------------------------
// Checks if a specific space is pressed.
bool checkPushPlace( GameObject *pSpace, IntPoint pushPosition );