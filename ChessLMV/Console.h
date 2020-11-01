#pragma once


#include <windows.h>


inline void HideConsole()
{
    ::ShowWindow(::GetConsoleWindow(), SW_HIDE);
}

inline void ShowConsole()
{
    ::ShowWindow(::GetConsoleWindow(), SW_SHOW);
}

inline bool IsConsoleVisible()
{
    return (::IsWindowVisible(::GetConsoleWindow()) != FALSE);
}
