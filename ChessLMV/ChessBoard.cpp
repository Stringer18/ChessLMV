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
            }
        }
    }
}



// ----------------------------------------------------------------------------
ChessBoard::~ChessBoard()
{
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
    if( m_IndexCellSelection.x == -1 )
    {
        // It's part, if figure didn`t select.
        // Next, check if we can select a figure in the clicked cell.
        if( ( pushIndex.x > -1 ) && ( pushIndex.x < 8 ) && (
                pushIndex.y > -1 ) && ( pushIndex.y < 8 ) && (
                m_board[pushIndex.x][pushIndex.y].m_pFigure != nullptr ) )
        {
            // !!! Add check black/white figure !!!
            // Select.
            m_IndexCellSelection = pushIndex;
            m_pCellSelection->setPosition( m_board[pushIndex.x][pushIndex.y].
                    getPosition() );
            m_gameWindow->addObjectForRenderer( m_pCellSelection );
            // This "return" is't need, but with it it's clearer and calmer.
            return; 
        }
    }
    else
    {
        // It's part, if figure selected.
        // Next, we check what to do with the selected figure - deselect or
        // make a move.
        if( ( pushIndex.x > -1 ) || ( pushIndex.x < 8 ) || (
                pushIndex.y > -1 ) || ( pushIndex.y < 8 ) || ( (
                pushIndex.x != m_IndexCellSelection.x ) && (
                pushIndex.y != m_IndexCellSelection.y ) ) )
        {
            // Move.
            // !!! Do not attack other pieces yet, not yet implemented.
            // !!! Will lead to memory leak.
            m_board[pushIndex.x][pushIndex.y].m_pFigure =
                    m_board[m_IndexCellSelection.x][m_IndexCellSelection.y].
                    m_pFigure;
            m_board[m_IndexCellSelection.x][m_IndexCellSelection.y].m_pFigure =
                    nullptr;
            m_board[pushIndex.x][pushIndex.y].m_pFigure->setPosition(
                    m_board[pushIndex.x][pushIndex.y].getPosition() );
        }

        // Deselect.
        m_gameWindow->deleteObjectFromRenderer( m_pCellSelection );
        m_IndexCellSelection = IntPoint( -1, -1 );
        m_pCellSelection->setPosition( m_sdlRect->x, m_sdlRect->y );
        // This "return" is't need, but with it it's clearer and calmer.
        return;
    }
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
    isBlackMove = !isBlackMove;
    m_pTextNowBlack->changeVisible();
    m_pTextNowWhite->changeVisible();
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
    SDL_Texture *sdlBuffTexture = nullptr;
    
    getDataFromIni( strBuff, "chessBoard", "strCellSelectionTexture",
            ".\\Resources\\CellSelection.png" );
    m_gameWindow->m_fIsSuccess = m_gameWindow->strPngTextureToSdlTexture(
            sdlBuffTexture, strBuff );

    m_pCellSelection = new GameObject( sdlBuffTexture, m_sdlRect->x,
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
    isBlackMove = false;

    int iTextPositionX = 0;
    int iTextPositionY = 0;
    int iTextWidthSize = 0;

    getDataFromIni( &iTextPositionX, "textNowMove", "iPositionX", 600);
    getDataFromIni( &iTextPositionY, "textNowMove", "iPositionY", 150);
    getDataFromIni( &iTextWidthSize, "textNowMove", "iWidthSize", 150);
            
    m_pTextNowBlack = new TextBox( m_gameWindow, "Now move: Black",
            IntPoint( iTextPositionX, iTextPositionY ), iTextWidthSize,
            isBlackMove );
    m_pTextNowWhite = new TextBox( m_gameWindow, "Now move: White",
            IntPoint( iTextPositionX, iTextPositionY ), iTextWidthSize,
            !isBlackMove );
    if( ( !( m_pTextNowBlack->isValid() ) ) || ( !( m_pTextNowWhite->isValid() ) ) )
    {
        setToLog( "Cannot create text section for board." );
        return false;
    }
    return true;
}