#pragma once

#include <stdio.h>
#include <Windows.h>
#include <ctime>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>



// ----------------------------------------------------------------------------
#define    _CHESSLMV_INI_       ".\\Resources\\ChessLMV.ini"
#define    _LOGFILE_LOG_        ".\\LogFile.log"
#define    _MAX_STR_BUFF_SIZE_  1024



// ----------------------------------------------------------------------------
template <typename T>
std::string valueAsString(T value)
{
    char buf[sizeof(T) + 1];
    strncpy_s( buf, sizeof(T) + 1, (const char*) &value, sizeof(T) );
	return std::string(buf);
}

template <typename T>
std::string toString(T value)
{
    std::ostringstream out_s;
    out_s << value;
    return out_s.str();
}



// ----------------------------------------------------------------------------
// Overloaded function for getting data (int/double/string) from ini-file.
void getDataFromIni( int *piData, char *szSection, char *szVarName,
        int iDefaultValue );
void getDataFromIni( double *pdblData, char *szSection, char *szVarName,
        double dblDefaultValue );
void getDataFromIni( std::string &strData, char *szSection, char *szVarName,
        char *szDefaultValue );



// ----------------------------------------------------------------------------
// The function takes the system time and returns it in the specified format.
void nowTimeInStr( std::string &strNowTime );



// ----------------------------------------------------------------------------
// The function receives a message, adds the current time and date to it and
// writes it to the log and console.
void setToLog( const std::string &strMessage );



// ----------------------------------------------------------------------------