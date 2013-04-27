// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#ifndef STRICT
#define STRICT
#endif

#ifndef WINVER				// Allow use of features specific to Windows 95 and Windows NT 4 or later.
#define WINVER 0x0600		// Change this to the appropriate value to target Windows 98 and Windows 2000 or later.
#endif

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows NT 4 or later.
#define _WIN32_WINNT 0x0600	// Change this to the appropriate value to target Windows 2000 or later.
#endif						

#ifndef _WIN32_IE			// Allow use of features specific to IE 4.0 or later.
#define _WIN32_IE 0x0600	// Change this to the appropriate value to target IE 5.0 or later.
#endif

#define _ATL_APARTMENT_THREADED
#define _ATL_NO_AUTOMATIC_NAMESPACE
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// some CString constructors will be explicit
#define _ATL_ALL_WARNINGS
#define ISOLATION_AWARE_ENABLED 1
#define  _WTL_NO_CSTRING

#include "resource.h"
#include <atlbase.h>
#include <atlcom.h>
#include <atlhost.h>
#include <atlapp.h>
#include <atlctrls.h>
#include <atldlgs.h>
#include <atlstr.h>

#include "VisualStylesXP.h"

#pragma warning( disable : 4278 )
#pragma warning( disable : 4146 )

#import "libid:AC0714F2-3D04-11D1-AE7D-00A0C90F26F4" version("1.0") lcid("0")  raw_interfaces_only no_implementation
#import "libid:{2df8d04c-5bfa-101b-bde5-00aa0044de52}" raw_interfaces_only no_implementation
#import "libid:{00021A98-0000-0000-C000-000000000046}" raw_interfaces_only no_implementation

#pragma warning( default : 4146 )
#pragma warning( default : 4278 )

class DECLSPEC_UUID("2445B4EC-CD68-4a61-B695-4ED95A69FB9D") MyAddin1Lib;

using namespace ATL;

class CAddInModule : public CAtlDllModuleT< CAddInModule >
{
public:
	DECLARE_LIBID(__uuidof(MyAddin1Lib))

	CAddInModule()
	{
		m_hInstance = NULL;
	}

	inline HINSTANCE GetResourceInstance()
	{
		return m_hInstance;
	}

	inline void SetResourceInstance(HINSTANCE hInstance)
	{
		m_hInstance = hInstance;
	}

private:
	HINSTANCE m_hInstance;
};

extern CAddInModule _AtlModule;