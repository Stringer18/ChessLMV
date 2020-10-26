#include "ChessBoard.h"

// ----------------------------------------------------------------------------
ChessBoard::ChessBoard( GameWindow *inputGameWindow ) :
        GameObjectInsertion( inputGameWindow )
{
    m_gameWindow->m_fIsSuccess = prepareBoard();
    if( m_gameWindow->m_fIsSuccess )
    {
        m_gameWindow->m_fIsSuccess = prepareFigures();
        if( m_gameWindow->m_fIsSuccess )
        {
            m_gameWindow->m_fIsSuccess = prepareText();
        }
    }
}



// ----------------------------------------------------------------------------
ChessBoard::~ChessBoard()
{
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

    if( pTextNowBlack != nullptr ) { delete pTextNowBlack; }
    if( pTextNowWhite != nullptr ) { delete pTextNowWhite; }

    m_gameWindow->deleteObjectFromRenderer( this );
}



// ----------------------------------------------------------------------------
void ChessBoard::pushAnalysis( IntPoint pushPoint )
{
    printf( "PushBoard = %i %i\n", pushPoint.x, pushPoint.y );
}



// ----------------------------------------------------------------------------
void ChessBoard::changeActualMove()
{
    isBlackMove = !isBlackMove;
    pTextNowBlack->changeVisible();
    pTextNowWhite->changeVisible();
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
    int iStepX = 0;
    int iStepY = 0;

    getDataFromIni( &iDeltaFirstFigurePositionX, "chessBoard",
            "iDeltaFirstFigurePositionX", 40 );
    getDataFromIni( &iDeltaFirstFigurePositionY, "chessBoard",
            "iDeltaFirstFigurePositionY", 40 );
    getDataFromIni( &iStepX, "chessBoard", "iStepX", 40 );
    getDataFromIni( &iStepY, "chessBoard", "iStepY", 40 );

    for( int j = 0 ; j < _BOARD_SIZE_ ; j++ )
    {
        for( int i = 0 ; i < _BOARD_SIZE_ ; i++ )
        {
            m_board[i][j].setPosition( m_sdlRect->x + 
                    iDeltaFirstFigurePositionX + i * iStepX,
                    m_sdlRect->y + iDeltaFirstFigurePositionY + j * iStepY );
        }
    }
}



// ----------------------------------------------------------------------------
bool ChessBoard::prepareFigures()
{
    int j = 0;
    m_board[0][j].m_pFigure = new BlackRook( m_gameWindow,
            m_board[0][j].getPosition() );
    m_board[7][j].m_pFigure = new BlackRook( m_gameWindow,
            m_board[7][j].getPosition() );
    
    m_board[1][j].m_pFigure = new BlackKnight( m_gameWindow,
            m_board[1][j].getPosition() );
    m_board[6][j].m_pFigure = new BlackKnight( m_gameWindow,
            m_board[6][j].getPosition() );

    m_board[2][j].m_pFigure = new BlackBishop( m_gameWindow,
            m_board[2][j].getPosition() );
    m_board[5][j].m_pFigure = new BlackBishop( m_gameWindow,
            m_board[5][j].getPosition() );

    m_board[3][j].m_pFigure = new BlackQueen( m_gameWindow,
            m_board[3][j].getPosition() );

    m_board[4][j].m_pFigure = new BlackKing( m_gameWindow,
            m_board[4][j].getPosition() );

    for( int i = 0 ; i < _BOARD_SIZE_ ; i++ )
    {
        m_board[i][1].m_pFigure = new BlackPawn( m_gameWindow,
                m_board[i][1].getPosition() );
        m_board[i][6].m_pFigure = new WhitePawn( m_gameWindow,
                m_board[i][6].getPosition() );
    }

    j = 7;
    m_board[0][j].m_pFigure = new WhiteRook( m_gameWindow,
            m_board[0][j].getPosition() );
    m_board[7][j].m_pFigure = new WhiteRook( m_gameWindow,
            m_board[7][j].getPosition() );
    
    m_board[1][j].m_pFigure = new WhiteKnight( m_gameWindow,
            m_board[1][j].getPosition() );
    m_board[6][j].m_pFigure = new WhiteKnight( m_gameWindow,
            m_board[6][j].getPosition() );

    m_board[2][j].m_pFigure = new WhiteBishop( m_gameWindow,
            m_board[2][j].getPosition() );
    m_board[5][j].m_pFigure = new WhiteBishop( m_gameWindow,
            m_board[5][j].getPosition() );

    m_board[3][j].m_pFigure = new WhiteQueen( m_gameWindow,
            m_board[3][j].getPosition() );

    m_board[4][j].m_pFigure = new WhiteKing( m_gameWindow,
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
            
    pTextNowBlack = new TextBox( m_gameWindow, "Now move: Black",
            IntPoint( iTextPositionX, iTextPositionY ), iTextWidthSize,
            isBlackMove );
    pTextNowWhite = new TextBox( m_gameWindow, "Now move: White",
            IntPoint( iTextPositionX, iTextPositionY ), iTextWidthSize,
            !isBlackMove );
    if( ( !( pTextNowBlack->isValid() ) ) || ( !( pTextNowWhite->isValid() ) ) )
    {
        setToLog( "Cannot create text section for board." );
        return false;
    }
    return true;
}