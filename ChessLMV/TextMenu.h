#pragma once

#include "GameWindow.h"
#include "TextBox.h"


// Defines for iCommandStore:
enum defineCommandTextMenu : int
{
    _NO_COMMAND_ = 0,
    _NEW_GAME_,
    _EXIT_,

    _COMMAND_TEXT_MENU_MAX_
};


// ----------------------------------------------------------------------------
class TextMenu : public GameObjectInsertion
{
    public:
        TextMenu( GameWindow *pGameWindow );
        ~TextMenu();


        // --------------------------------------------------------------------
        // Check the place of the click and performs actions based
        // on the context. This function is called when there was a click
        // to some place on menu.
        int pushAnalysis( IntPoint pushPoint );


    // ------------------------------------------------------------------------
    protected:
        // Checks if a specific button in menu has been pressed.
        bool checkPushButton( TextBox * pButton, IntPoint pushPoint );

        TextBox *pTextNewGame;
        TextBox *pTextExit;
        TextBox *pTextYes;
        TextBox *pTextNo;

        // Remembers here which command was selected (in the menu) to wait
        // for confirmation.
        int iCommandStore;
};