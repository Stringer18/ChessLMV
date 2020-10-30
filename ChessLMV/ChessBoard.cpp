#include "ChessBoard.h"

// ----------------------------------------------------------------------------
ChessBoard::ChessBoard( GameWindow *pGameWindow ) :
        GameObjectInsertion( pGameWindow )
{
    m_gameWindow->m_fIsSuccess = prepareBoard();
    if( m_gameWindow->m_fIsSuccess )
    {
        m_gameWindow->m_fIsSuccess = prepareCellSelection();
        if( m_gameWindow->m_fIsSuccess )
        {
            m_gameWindow->m_fIsSuccess = prepareFigures();
            if( m_gameWindow->m_fIsSuccess )
            {
                m_gameWindow->m_fIsSuccess = prepareText();
                if( m_gameWindow->m_fIsSuccess )
                {
                    m_gameWindow->m_fIsSuccess = preparePawnPromotion();
                }
            }
        }
    }
    m_lastMoveFrom = IntPoint( -1, -1 );
    m_lastMoveTo = IntPoint( -1, -1 );
}



// ----------------------------------------------------------------------------
ChessBoard::~ChessBoard()
{
    m_gameWindow->deleteObjectFromRenderer( m_pBlackPawnPromotion );
    m_gameWindow->deleteObjectFromRenderer( m_pWhitePawnPromotion );
    if( m_pBlackPawnPromotion != nullptr ) { delete m_pBlackPawnPromotion; }
    if( m_pWhitePawnPromotion != nullptr ) { delete m_pWhitePawnPromotion; }
    if( m_pTextChangePawn != nullptr ) { delete m_pTextChangePawn; }


    m_gameWindow->deleteObjectFromRenderer( m_pCellSelection );
    if( m_pCellSelection != nullptr ) { delete m_pCellSelection; }
    

    for( int j = 0 ; j < _BOARD_SIZE_ ; j++ )
    {
        for( int i = 0 ; i < _BOARD_SIZE_ ; i++ )
        {
            if( m_board[i][j].m_pFigure != nullptr )
            {
                m_gameWindow->deleteObjectFromRenderer(
                        m_board[i][j].m_pFigure );
                delete m_board[i][j].m_pFigure;
            }
        }
    }


    if( m_pTextNowBlack != nullptr ) { delete m_pTextNowBlack; }
    if( m_pTextNowWhite != nullptr ) { delete m_pTextNowWhite; }

    m_gameWindow->deleteObjectFromRenderer( this );
}



// ----------------------------------------------------------------------------
void ChessBoard::pushAnalysis( IntPoint pushPoint )
{
    IntPoint pushIndex = pushPointToCellPoint( pushPoint );

    if( m_fIsPawnPromotionActive )
    {
        pawnPromotion( pushIndex );
        return;
    }

    if( m_IndexCellSelection == IntPoint( -1, -1 ) )
    {
        // It's part, if figure didn`t select.
        // Next, check if we can select a figure in the clicked cell.
        if( isOnBoardIndex( pushIndex ) )
        {
            if( m_board[pushIndex.x][pushIndex.y].m_pFigure != nullptr )
            {
                if( m_board[pushIndex.x][pushIndex.y].m_pFigure->getColor() ==
                    m_isBlackMove )
                {
                    selectFigure( pushIndex );
                    return;
                }
            }
        }
    }
    else
    {
        // It's part, if figure selected.
        // Next, we check what to do with the selected figure - deselect or
        // make a move.
        if( isOnBoardIndex( pushIndex ) && ( pushIndex != m_IndexCellSelection ) )
        {
            // ----------------------------------------------------------------
            // This is where the standard movements are checked (and executed).
            if( checkMoveFigure( m_IndexCellSelection, pushIndex ) )
            {
                if( m_board[pushIndex.x][pushIndex.y].m_pFigure == nullptr)
                {
                    moveFigure( pushIndex );
                }
                else
                {
                    atackFigure( pushIndex );
                }
            }

            // ----------------------------------------------------------------
            // Checking special rules.
            pawnPromotion( pushIndex );
            pawnTakingPass( pushIndex );
            kingCastling( pushIndex );
        }
        if( !m_fIsPawnPromotionActive ) { deselectFigure(); }
        return;
    }
}



// ----------------------------------------------------------------------------
bool ChessBoard::isOnBoardIndex( IntPoint checkIndex )
{
    return ( ( checkIndex.x > -1 ) && ( checkIndex.x < _BOARD_SIZE_ ) &&
            ( checkIndex.y > -1 ) && ( checkIndex.y < _BOARD_SIZE_ ) );
}



// ----------------------------------------------------------------------------
IntPoint ChessBoard::pushPointToCellPoint( IntPoint pushPoint )
{
    int iIndexX = (int) ( floor( ( (double) pushPoint.x -
            m_board[0][0].getPosition().x ) / m_iStepX ) );
    int iIndexY = (int) ( floor( ( (double) pushPoint.y -
            m_board[0][0].getPosition().y ) / m_iStepY ) );
    return IntPoint( iIndexX, iIndexY );
}



// ----------------------------------------------------------------------------
void ChessBoard::changeActualMove()
{
    m_isBlackMove = !m_isBlackMove;
    m_pTextNowBlack->changeVisible();
    m_pTextNowWhite->changeVisible();
}



// ----------------------------------------------------------------------------
void ChessBoard::selectFigure( IntPoint pushIndex )
{
    m_IndexCellSelection = pushIndex;
    m_pCellSelection->setPosition(
            m_board[pushIndex.x][pushIndex.y].getPosition() );
    m_gameWindow->addObjectForRenderer( m_pCellSelection );
}



// ----------------------------------------------------------------------------
void ChessBoard::deselectFigure()
{
    m_gameWindow->deleteObjectFromRenderer( m_pCellSelection );
    m_IndexCellSelection = IntPoint( -1, -1 );
    m_pCellSelection->setPosition( m_sdlRect->x, m_sdlRect->y );
}



// ----------------------------------------------------------------------------
bool ChessBoard::checkMoveFigure( IntPoint selectIndex, IntPoint pushIndex )
{
    if( !isOnBoardIndex( selectIndex ) || !isOnBoardIndex( pushIndex ) ||
            ( selectIndex == pushIndex ) )
    {
        return false;
    }

    IntPoint moveVector = m_board[selectIndex.x][selectIndex.y].m_pFigure->
            checkTrajectory( selectIndex, pushIndex,
            m_board[pushIndex.x][pushIndex.y].m_pFigure );

    if( moveVector == IntPoint( 0, 0 ) )
    {
        return false;
    }

    // If moveVector turns out to be incorrect, then this
    // type of cycle will limit the number of checks in accordance
    // with the size of the board.
    IntPoint focusIndex = selectIndex.plusPoint( moveVector );
    for( int i = 1 ; i < _BOARD_SIZE_ ; i++ )
    {
        if( focusIndex == pushIndex )
        {
            return true;
        }
        if( m_board[focusIndex.x][focusIndex.y].m_pFigure != nullptr )
        {
            return false;
        }
        focusIndex = focusIndex.plusPoint( moveVector );
    }
    
    // If we got here, then moveVector turned out to be wrong.
    setToLog( "Incorrect moveVector." );
    return false;
}



// ----------------------------------------------------------------------------
void ChessBoard::moveFigure( IntPoint pushIndex )
{
    if( m_IndexCellSelection == IntPoint( -1, -1 ) )
    {
        setToLog( "Cannot move figure. It is not selected." );
        m_gameWindow->m_fIsSuccess = false;
        return;
    }
    m_lastMoveFrom = m_IndexCellSelection;
    m_lastMoveTo = pushIndex;
    m_board[m_lastMoveTo.x][m_lastMoveTo.y].m_pFigure =
            m_board[m_lastMoveFrom.x][m_lastMoveFrom.y].
            m_pFigure;
    m_board[m_lastMoveFrom.x][m_lastMoveFrom.y].m_pFigure =
            nullptr;
    m_board[m_lastMoveTo.x][m_lastMoveTo.y].m_pFigure->setPosition(
            m_board[m_lastMoveTo.x][m_lastMoveTo.y].getPosition() );
    changeActualMove();
}



// ----------------------------------------------------------------------------
void ChessBoard::atackFigure( IntPoint atackIndex )
{
    if( m_IndexCellSelection == IntPoint( -1, -1 ) )
    {
        setToLog( "Impossible to attack. Selection is empty." );
        m_gameWindow->m_fIsSuccess = false;
        return;
    }
    if( m_board[m_IndexCellSelection.x][m_IndexCellSelection.y].m_pFigure->
            getColor() == m_board[atackIndex.x][atackIndex.y].m_pFigure->
            getColor() )
    {
        return;
    }

    // m_pFigure == nullptr if we use a special rule - "taking on the pass".
    if( m_board[atackIndex.x][atackIndex.y].m_pFigure != nullptr )
    {
        delete m_board[atackIndex.x][atackIndex.y].m_pFigure;
    }
    moveFigure( atackIndex );
}



// ----------------------------------------------------------------------------
void ChessBoard::pawnPromotion( IntPoint pushIndex )
{
    // Two-step protection against accidental errors due to incorrect data.
    if( !( isOnBoardIndex( m_lastMoveTo ) ) )
    {
        return;
    }

    Figure *pBuffFigure = m_board[m_lastMoveTo.x][m_lastMoveTo.y].m_pFigure;
    if( pBuffFigure== nullptr )
    {
        return;
    }

    // ------------------------------------------------------------------------
    bool fBuffColor = pBuffFigure->getColor();
    if( m_fIsPawnPromotionActive )
    {
        // Selection new type of figure and turning a pawn into it.
        if( ( pushIndex.x >= iIndexXStartSelectionPawnPromotion ) &&
                ( pushIndex.x < iIndexXStartSelectionPawnPromotion + 5 ) &&
                ( pushIndex.y == -1 ) )
        {
            delete m_board[m_lastMoveTo.x][m_lastMoveTo.y].m_pFigure;
            m_board[m_lastMoveTo.x][m_lastMoveTo.y].m_pFigure = new Figure(
                    m_gameWindow, fBuffColor, pushIndex.x -
                    iIndexXStartSelectionPawnPromotion,
                    m_board[m_lastMoveTo.x][m_lastMoveTo.y].getPosition() );
            if( m_board[m_lastMoveTo.x][m_lastMoveTo.y].m_pFigure->isValid() )
            {
                setToLog( "Cannot create new figure in pawn promotion." );
                m_gameWindow->m_fIsSuccess = false;
            }

            if( fBuffColor )
            {
                m_gameWindow->deleteObjectFromRenderer( m_pBlackPawnPromotion);
            }
            else
            {
                m_gameWindow->deleteObjectFromRenderer( m_pWhitePawnPromotion);
            }
            m_fIsPawnPromotionActive = false;
            m_pTextChangePawn->changeVisible();
            deselectFigure();
            changeActualMove();
        }
    }
    else
    {
        // Checking and activating the mode of pawn promotion.
        if( ( pBuffFigure->getType() == _PAWN_ ) && ( m_lastMoveTo.y == 
                ( fBuffColor ? ( _BOARD_SIZE_ - 1) : 0 ) ) )
        {
            if( fBuffColor )
            {
                m_gameWindow->addObjectForRenderer( m_pBlackPawnPromotion );
            }
            else
            {
                m_gameWindow->addObjectForRenderer( m_pWhitePawnPromotion );
            }
            m_fIsPawnPromotionActive = true;
            m_pTextChangePawn->changeVisible();
            selectFigure( pushIndex );
            changeActualMove();
        }
    }
}



// ----------------------------------------------------------------------------
void ChessBoard::pawnTakingPass( IntPoint pushIndex )
{
    // Two-step protection against accidental errors due to incorrect data.
    if( !( isOnBoardIndex( m_lastMoveFrom ) ) ||
            !( isOnBoardIndex( m_lastMoveTo ) ) ||
            !( isOnBoardIndex( pushIndex ) ) ||
            !( isOnBoardIndex( m_IndexCellSelection ) ) ) 
    {
        return;
    }

    Figure *pOpponentPawn = m_board[m_lastMoveTo.x][m_lastMoveTo.y].m_pFigure;
    Figure *pOwnPawn =
            m_board[m_IndexCellSelection.x][m_IndexCellSelection.y].m_pFigure;

    if( ( pOpponentPawn == nullptr ) || ( pOwnPawn == nullptr ) )
    {
        return;
    }

    // ------------------------------------------------------------------------
    if( ( pOpponentPawn->getType() == _PAWN_ ) &&
            ( pOwnPawn->getType() == _PAWN_ ) &&
            ( pushIndex.x == m_lastMoveFrom.x ) &&
            ( pushIndex.x == m_lastMoveTo.x ) &&
            ( abs ( pushIndex.x - m_IndexCellSelection.x ) == 1 ) &&
            ( m_lastMoveTo.y == m_IndexCellSelection.y ) &&
            ( abs ( m_lastMoveFrom.y - m_lastMoveTo.y ) == 2 ) &&
            ( pushIndex.y == ( ( m_lastMoveFrom.y + m_lastMoveTo.y ) / 2 ) ) )
    {
        IntPoint startAtack = m_IndexCellSelection;
        atackFigure( m_lastMoveTo );
        selectFigure( m_lastMoveTo );
        moveFigure( pushIndex );
        m_lastMoveFrom = startAtack;
        changeActualMove();
    }
}



// ----------------------------------------------------------------------------
void ChessBoard::kingCastling( IntPoint pushIndex )
{
    if( ( !isOnBoardIndex( m_IndexCellSelection ) ) ||
            ( !isOnBoardIndex( pushIndex ) ) )
    {
        return;
    }

    Figure *pKing =
            m_board[m_IndexCellSelection.x][m_IndexCellSelection.y].m_pFigure;
    if( pKing == nullptr ) { return; }

    if( ( pKing->getType() == _KING_ ) && ( pKing->getIsMoved() == false ) &&
            ( abs( pushIndex.x - m_IndexCellSelection.x ) == 2 ) &&
            ( pushIndex.y == m_IndexCellSelection.y ) )
    {
        if( pushIndex.x < m_IndexCellSelection.x )
        {
            // ----------------------------------------------------------------
            // Long castling.

            if( m_board[0][pushIndex.y].m_pFigure->getType() != _ROOK_ )
            {
                return;
            }

            // Checking the path for the absence of a check.
            for( int i = pushIndex.x ; i <= m_IndexCellSelection.x ; i++ )
            {
                if( checkCheck( IntPoint( i, pushIndex.y ) ) ) { return; }
            }

            // Checking the path for the absence of obstacles.
            for( int i = 1 ; i < m_IndexCellSelection.x ; i++ )
            {
                if( m_board[i][pushIndex.y].m_pFigure != nullptr ) { return; }
            }

            // ----------------------------------------------------------------
            // Carry out castling.
            moveFigure( pushIndex );
            deselectFigure();
            changeActualMove();
            selectFigure( IntPoint( 0, pushIndex.y ) );
            moveFigure( pushIndex.plusPoint( 1, 0 ) );
        }
        else
        {
            // ----------------------------------------------------------------
            // Short castling.

            if( m_board[_BOARD_SIZE_-1][pushIndex.y].m_pFigure->getType() !=
                    _ROOK_ )
            {
                return;
            }

            // Checking the path for the absence of a check.
            for( int i = m_IndexCellSelection.x ; i <= pushIndex.x ; i++ )
            {
                if( checkCheck( IntPoint( i, pushIndex.y ) ) ) { return; }
            }

            // Checking the path for the absence of obstacles.
            for( int i = m_IndexCellSelection.x + 1 ; i < _BOARD_SIZE_ - 1 ; i++ )
            {
                if( m_board[i][pushIndex.y].m_pFigure != nullptr ) { return; }
            }

            // ----------------------------------------------------------------
            // Carry out castling.
            moveFigure( pushIndex );
            deselectFigure();
            changeActualMove();
            selectFigure( IntPoint( _BOARD_SIZE_ - 1, pushIndex.y ) );
            moveFigure( pushIndex.plusPoint( -1, 0 ) );
        }
    }
}



// ----------------------------------------------------------------------------
bool ChessBoard::checkCheck( IntPoint checkIndex )
{
    if( !isOnBoardIndex( checkIndex ) ) { return false; }

    for( int j = 0 ; j < _BOARD_SIZE_ ; j++ )
    {
        for( int i = 0 ; i < _BOARD_SIZE_ ; i++ )
        {
            if( m_board[i][j].m_pFigure == nullptr ) { continue; }
            if( m_board[i][j].m_pFigure->getColor() != m_isBlackMove )
            {
                if( checkMoveFigure( IntPoint( i, j ), checkIndex ) )
                {
                    return true;
                }
            }
        }
    }
    return false;
}



// ----------------------------------------------------------------------------
bool ChessBoard::checkCheckKing()
{
    return checkCheck( findKing() );
}



// ----------------------------------------------------------------------------
IntPoint ChessBoard::findKing()
{
    for( int j = 0 ; j < _BOARD_SIZE_ ; j++ )
    {
        for( int i = 0 ; i < _BOARD_SIZE_ ; i++ )
        {
            if( m_board[i][j].m_pFigure == nullptr ) { continue; }
            if( ( m_board[i][j].m_pFigure->getColor() == m_isBlackMove ) &&
                ( m_board[i][j].m_pFigure->getType() == _KING_ ) )
            {
                return IntPoint( i, j );
            }
        }
    }
    return IntPoint( -1, -1 );
}



// ----------------------------------------------------------------------------
bool ChessBoard::prepareBoard()
{
    std::string strBuff("");
    getDataFromIni( strBuff, "chessBoard", "strTexture",
            ".\\Resources\\ChessBoard.png" );
    m_gameWindow->m_fIsSuccess = m_gameWindow->strPngTextureToSdlTexture(
            m_sdlTexture, strBuff );
    if( !( m_gameWindow->m_fIsSuccess ) )
    {
        setToLog( "Chess board texture didn't create." );
        return false;
    }
    getDataFromIni( &(m_sdlRect->x), "chessBoard", "iPositionX", 100 );
    getDataFromIni( &(m_sdlRect->y), "chessBoard", "iPositionY", 100 );
    getDataFromIni( &(m_sdlRect->w), "chessBoard", "iWidth", 400 );
    getDataFromIni( &(m_sdlRect->h), "chessBoard", "iHeight", 400 );

    prepareGridBoard();
    m_gameWindow->addObjectForRenderer( this );
    return true;
}



// ----------------------------------------------------------------------------
void ChessBoard::prepareGridBoard()
{
    int iDeltaFirstFigurePositionX = 0;
    int iDeltaFirstFigurePositionY = 0;

    getDataFromIni( &iDeltaFirstFigurePositionX, "chessBoard",
            "iDeltaFirstFigurePositionX", 40 );
    getDataFromIni( &iDeltaFirstFigurePositionY, "chessBoard",
            "iDeltaFirstFigurePositionY", 40 );
    getDataFromIni( &m_iStepX, "chessBoard", "iStepX", 40 );
    getDataFromIni( &m_iStepY, "chessBoard", "iStepY", 40 );

    for( int j = 0 ; j < _BOARD_SIZE_ ; j++ )
    {
        for( int i = 0 ; i < _BOARD_SIZE_ ; i++ )
        {
            m_board[i][j].setPosition( m_sdlRect->x + 
                    iDeltaFirstFigurePositionX + i * m_iStepX,
                    m_sdlRect->y + iDeltaFirstFigurePositionY + j * m_iStepY );
        }
    }
}



// ----------------------------------------------------------------------------
bool ChessBoard::prepareCellSelection()
{
    m_IndexCellSelection = IntPoint( -1, -1 );

    std::string strBuff("");
    SDL_Texture *psdlBuffTexture = nullptr;
    
    getDataFromIni( strBuff, "chessBoard", "strCellSelectionTexture",
            ".\\Resources\\CellSelection.png" );
    m_gameWindow->m_fIsSuccess = m_gameWindow->strPngTextureToSdlTexture(
            psdlBuffTexture, strBuff );

    m_pCellSelection = new GameObject( psdlBuffTexture, m_sdlRect->x,
            m_sdlRect->y, m_iStepX, m_iStepY );

    if( !( m_gameWindow->m_fIsSuccess ) )
    {
        setToLog( "Cell Selection texture didn't create." );
        return false;
    }

    return true;
}



// ----------------------------------------------------------------------------
bool ChessBoard::prepareFigures()
{
    int j = 0;
    m_board[0][j].m_pFigure = new Figure( m_gameWindow, true, _ROOK_,
            m_board[0][j].getPosition() );
    m_board[7][j].m_pFigure = new Figure( m_gameWindow, true, _ROOK_,
            m_board[7][j].getPosition() );
    
    m_board[1][j].m_pFigure = new Figure( m_gameWindow, true, _KNIGHT_,
            m_board[1][j].getPosition() );
    m_board[6][j].m_pFigure = new Figure( m_gameWindow, true, _KNIGHT_,
            m_board[6][j].getPosition() );

    m_board[2][j].m_pFigure = new Figure( m_gameWindow, true, _BISHOP_,
            m_board[2][j].getPosition() );
    m_board[5][j].m_pFigure = new Figure( m_gameWindow, true, _BISHOP_,
            m_board[5][j].getPosition() );

    m_board[3][j].m_pFigure = new Figure( m_gameWindow, true, _QUEEN_,
            m_board[3][j].getPosition() );

    m_board[4][j].m_pFigure = new Figure( m_gameWindow, true, _KING_,
            m_board[4][j].getPosition() );

    for( int i = 0 ; i < _BOARD_SIZE_ ; i++ )
    {
        m_board[i][1].m_pFigure = new Figure( m_gameWindow, true, _PAWN_,
                m_board[i][1].getPosition() );
        m_board[i][6].m_pFigure = new Figure( m_gameWindow, false, _PAWN_,
                m_board[i][6].getPosition() );
    }

    j = 7;
    m_board[0][j].m_pFigure = new Figure( m_gameWindow, false, _ROOK_,
            m_board[0][j].getPosition() );
    m_board[7][j].m_pFigure = new Figure( m_gameWindow, false, _ROOK_,
            m_board[7][j].getPosition() );
    
    m_board[1][j].m_pFigure = new Figure( m_gameWindow, false,  _KNIGHT_,
            m_board[1][j].getPosition() );
    m_board[6][j].m_pFigure = new Figure( m_gameWindow, false,  _KNIGHT_,
            m_board[6][j].getPosition() );

    m_board[2][j].m_pFigure = new Figure( m_gameWindow, false, _BISHOP_,
            m_board[2][j].getPosition() );
    m_board[5][j].m_pFigure = new Figure( m_gameWindow, false, _BISHOP_,
            m_board[5][j].getPosition() );

    m_board[3][j].m_pFigure = new Figure( m_gameWindow, false, _QUEEN_,
            m_board[3][j].getPosition() );

    m_board[4][j].m_pFigure = new Figure( m_gameWindow, false, _KING_,
            m_board[4][j].getPosition() );

    // Check figures.
    for( j = 0 ; j < _BOARD_SIZE_ ; j++ )
    {
        if( j == 2 ) { j = 6; } // Skip nullptr part of board.
        for( int i = 0 ; i < _BOARD_SIZE_ ; i++ )
        {
            if( !( m_board[i][j].m_pFigure->isValid() ) )
            {
                setToLog( std::string( "There are problems with creating " ) +
                        "and/or filling the playing field." );
                return false;
            }
        }
    }
    return true;
}



// ----------------------------------------------------------------------------
bool ChessBoard::prepareText()
{
    m_isBlackMove = false;

    int iTextPositionX = 0;
    int iTextPositionY = 0;
    int iTextWidthSize = 0;

    getDataFromIni( &iTextPositionX, "textNowMove", "iPositionX", 600);
    getDataFromIni( &iTextPositionY, "textNowMove", "iPositionY", 150);
    getDataFromIni( &iTextWidthSize, "textNowMove", "iWidthSize", 150);
            
    m_pTextNowBlack = new TextBox( m_gameWindow, "Now move: Black",
            IntPoint( iTextPositionX, iTextPositionY ), iTextWidthSize,
            m_isBlackMove );
    m_pTextNowWhite = new TextBox( m_gameWindow, "Now move: White",
            IntPoint( iTextPositionX, iTextPositionY ), iTextWidthSize,
            !m_isBlackMove );

    if( ( !( m_pTextNowBlack->isValid() ) ) ||
            ( !( m_pTextNowWhite->isValid() ) ) )
    {
        setToLog( "Cannot create text section for board." );
        return false;
    }

    return true;
}



// ----------------------------------------------------------------------------
bool ChessBoard::preparePawnPromotion()
{
    m_fIsPawnPromotionActive = false;

    int iDeltaX = 0;
    int iDeltaY = 0;
    int iTextWidthSize = 0;

    getDataFromIni( &iDeltaX, "chessBoard", "iDeltaFirstFigurePositionX", 40 );
    getDataFromIni( &iDeltaY, "chessBoard", "iDeltaFirstFigurePositionY", 40 );
    getDataFromIni( &iTextWidthSize, "textNowMove", "iWidthSize", 150);
    getDataFromIni( &iIndexXStartSelectionPawnPromotion, "pawnPromotion",
            "iIndexXStartSelection", 3);

    m_pTextChangePawn = new TextBox( m_gameWindow, "Change pawn to:",
            IntPoint( m_sdlRect->x, m_sdlRect->y ), iTextWidthSize,
            m_fIsPawnPromotionActive );
    m_pTextChangePawn->setPosition( m_sdlRect->x + iDeltaX / 4, m_sdlRect->y +
            ( iDeltaY - m_pTextChangePawn->getSize().y ) / 2 );

    std::string strBuff("");

    SDL_Texture *psdlBlackTexture = nullptr;
    getDataFromIni( strBuff, "pawnPromotion", "strBlack",
            ".\\Resources\\BlackPawnPromotion.png" );
    m_gameWindow->m_fIsSuccess = m_gameWindow->strPngTextureToSdlTexture(
            psdlBlackTexture, strBuff );
    m_pBlackPawnPromotion = new GameObject( psdlBlackTexture,
            m_board[iIndexXStartSelectionPawnPromotion][0].getPosition().x,
            m_sdlRect->y, m_iStepX * 5, m_iStepY );

    SDL_Texture *psdlWhiteTexture = nullptr;
    getDataFromIni( strBuff, "pawnPromotion", "strWhite",
            ".\\Resources\\WhitePawnPromotion.png" );
    m_gameWindow->m_fIsSuccess = m_gameWindow->strPngTextureToSdlTexture(
            psdlWhiteTexture, strBuff );
    m_pWhitePawnPromotion = new GameObject( psdlWhiteTexture,
            m_board[iIndexXStartSelectionPawnPromotion][0].getPosition().x,
            m_sdlRect->y, m_iStepX * 5, m_iStepY );


    if( ( !( m_pTextChangePawn->isValid() ) ) ||
                ( !( m_pBlackPawnPromotion->isValid() ) ) ||
                ( !( m_pWhitePawnPromotion->isValid() ) ) )
    {
        setToLog( "Cannot create object(s) for pawn promotion on the board." );
        return false;
    }

    return true;
}