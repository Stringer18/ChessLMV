#include "HelpFunctions.hpp"



// ----------------------------------------------------------------------------
void getDataFromIni( int *piData, char *szSection, char *szVarName,
        int iDefaultValue )
{
    char szBuff [_MAX_STR_BUFF_SIZE_];

    GetPrivateProfileString( szSection, szVarName, "ErrorString", szBuff,
            _MAX_STR_BUFF_SIZE_, _CHESSLMV_INI_ );

    if( strcmp( szBuff, "ErrorString" ) == 0 )
    {
        setToLog( std::string( "Error. Unable to get data from ini-file." ) +
                "\n\tFile = \"" + _CHESSLMV_INI_ +
                "\"\n\tSection = \"" + szSection +
                "\"\n\tVariable Name = \"" + szVarName +
                "\"\n\tDefault Value = \"" + toString( iDefaultValue ) +
                "\"\n\tFunction return default value." );
        *piData = iDefaultValue;
    }
    else
    {
        *piData = atoi( szBuff );
    }
}



void getDataFromIni( double *pdblData, char *szSection, char *szVarName,
        double dblDefaultValue )
{
    char szBuff [_MAX_STR_BUFF_SIZE_];

    GetPrivateProfileString( szSection, szVarName, "ErrorString", szBuff,
            _MAX_STR_BUFF_SIZE_, _CHESSLMV_INI_ );

    if( strcmp( szBuff, "ErrorString" ) == 0 )
    {
        setToLog( std::string( "Error. Unable to get data from ini-file." ) +
                "\n\tFile = \"" + _CHESSLMV_INI_ +
                "\"\n\tSection = \"" + szSection +
                "\"\n\tVariable Name = \"" + szVarName +
                "\"\n\tDefault Value = \"" + toString( dblDefaultValue ) +
                "\"\n\tFunction return default value." );
        *pdblData = dblDefaultValue;
    }
    else
    {
        *pdblData = atof( szBuff );
    }
}



void getDataFromIni( std::string &strData, char *szSection, char *szVarName,
       char *szDefaultValue )
{
    char szBuff [_MAX_STR_BUFF_SIZE_];

    GetPrivateProfileString( szSection, szVarName, "ErrorString", szBuff,
            _MAX_STR_BUFF_SIZE_, _CHESSLMV_INI_ );

    if( strcmp( szBuff, "ErrorString" ) == 0 )
    {
        setToLog( std::string( "Error. Unable to get data from ini-file." ) +
                "\n\tFile = \"" + _CHESSLMV_INI_ +
                "\"\n\tSection = \"" + szSection +
                "\"\n\tVariable Name = \"" + szVarName +
                "\"\n\tDefault Value = \"" + szDefaultValue +
                "\"\n\tFunction return default value." );
        strData = szDefaultValue;
    }
    else
    {
        strData = szBuff;
    }
}



// ----------------------------------------------------------------------------
void nowTimeInStr( std::string &strNowTime )
{
    time_t rawTime;
    time ( &rawTime );
    
    struct tm timeInfo;
    localtime_s ( &timeInfo, &rawTime );
    
    char szBuff [_MAX_STR_BUFF_SIZE_];
    strftime ( szBuff, _MAX_STR_BUFF_SIZE_, "%Y-%m-%d_%H:%M:%S", &timeInfo);
    strNowTime.append( szBuff );
}



// ----------------------------------------------------------------------------
void setToLog( const std::string &strMessage )
{
    std::string strLogMessage("");
    nowTimeInStr( strLogMessage );
    strLogMessage += " --- " + strMessage + "\n";

    printf( "%s", strLogMessage.c_str() );

    FILE *logFile;
    if ( fopen_s( &logFile, _LOGFILE_LOG_, "a" ) != 0 )
    {
        printf( "Cannot open %s\nMessage didn't add to log.\n", _LOGFILE_LOG_);
        return;
    }
    fprintf( logFile, "%s", strLogMessage.c_str() );
    fclose( logFile );
}



// ----------------------------------------------------------------------------