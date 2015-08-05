// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#ifndef STRICT
#define STRICT
#endif

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#endif						

#ifndef _WIN32_IE			// Allow use of features specific to IE 4.0 or later.
#define _WIN32_IE 0x0700	// Change this to the appropriate value to target IE 5.0 or later.
#endif

#define _ATL_APARTMENT_THREADED
#define _ATL_NO_AUTOMATIC_NAMESPACE
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// some CString constructors will be explicit
#define _ATL_ALL_WARNINGS
#define ISOLATION_AWARE_ENABLED		1

#include "resource.h"

#include <afxwin.h>
#include <commctrl.h>
#include <atlbase.h>
#include <atlcom.h>

#include <Scintilla.h>
#include <SciLexer.h>

#include "import\IDTExtensibility2.tlh"
#include "import\MSO.tlh"
#include "import\VISLIB.tlh"

using namespace ATL;
