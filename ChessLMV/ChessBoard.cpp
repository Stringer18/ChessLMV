#include "ChessBoard.h"

// ----------------------------------------------------------------------------
ChessBoard::ChessBoard( GameWindow *inputGameWindow ) :
        GameObjectInsertion( inputGameWindow )
{
    std::string strBuff("");
    getDataFromIni( strBuff, "chessBoard", "strTexture",
            ".\\Resources\\ChessBoard.png" );
    m_gameWindow->m_fIsSuccess = m_gameWindow->strPngTextureToSdlTexture(
            m_sdlTexture, strBuff );

    if( m_gameWindow->m_fIsSuccess )
    {
        getDataFromIni( &(m_sdlRect->x), "chessBoard", "iPositionX", 100 );
        getDataFromIni( &(m_sdlRect->y), "chessBoard", "iPositionY", 100 );
        getDataFromIni( &(m_sdlRect->w), "chessBoard", "iWidth", 400 );
        getDataFromIni( &(m_sdlRect->h), "chessBoard", "iHeight", 400 );
        m_gameWindow->addObjectForRenderer( this );

        prepareGridBoard();
        m_gameWindow->m_fIsSuccess = prepareFigures();
        if( !( m_gameWindow->m_fIsSuccess ) )
        {
            setToLog( std::string( "There are problems with creating " ) +
                    "and/or filling the playing field." );
        }

    }
    else
    {
        setToLog( "Chess board texture didn't create." );
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
    m_gameWindow->deleteObjectFromRenderer( this );
    m_gameWindow->refresh();
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

    return true;
}



// ----------------------------------------------------------------------------