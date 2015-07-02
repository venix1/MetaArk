// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#include <DbgHelp.h>
#include <Shlwapi.h>
#include <Shlobj.h>

// C++ std
#include <algorithm>
#include <fstream>
#include <unordered_map>
#include <string>

// Application
#include "MinHook.h"