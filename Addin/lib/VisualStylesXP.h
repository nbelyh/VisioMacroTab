#ifndef _VISUALSTYLE_XP_H_
#define _VISUALSTYLE_XP_H_

#pragma once

#include <uxtheme.h>

class CVisualStylesXP
{
private:
	HMODULE m_hThemeDll;
	void* GetProc(LPCSTR szProc, void* pfnFail);

	typedef HTHEME(__stdcall *PFNOPENTHEMEDATA)(HWND hwnd, LPCWSTR pszClassList);
	static HTHEME __stdcall OpenThemeDataFail(HWND , LPCWSTR )
	{return NULL;}

	typedef HRESULT(__stdcall *PFNCLOSETHEMEDATA)(HTHEME hTheme);
	static HRESULT __stdcall CloseThemeDataFail(HTHEME)
	{return E_FAIL;}

	typedef HRESULT(__stdcall *PFNDRAWTHEMEBACKGROUND)(HTHEME hTheme, HDC hdc, 
		int iPartId, int iStateId, const RECT *pRect,  const RECT *pClipRect);
	static HRESULT __stdcall DrawThemeBackgroundFail(HTHEME, HDC, int, int, const RECT *, const RECT *)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNDRAWTHEMETEXT)(HTHEME hTheme, HDC hdc, int iPartId, 
		int iStateId, LPCWSTR pszText, int iCharCount, DWORD dwTextFlags, 
		DWORD dwTextFlags2, const RECT *pRect);
	static HRESULT __stdcall DrawThemeTextFail(HTHEME, HDC, int, int, LPCWSTR, int, DWORD, DWORD, const RECT*)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNGETTHEMEBACKGROUNDCONTENTRECT)(HTHEME hTheme,  HDC hdc, 
		int iPartId, int iStateId,  const RECT *pBoundingRect, 
		RECT *pContentRect);
	static HRESULT __stdcall GetThemeBackgroundContentRectFail(HTHEME hTheme,  HDC hdc, 
		int iPartId, int iStateId,  const RECT *pBoundingRect, 
		RECT *pContentRect)
	{return E_FAIL;}
	typedef HRESULT (__stdcall *PFNGETTHEMEBACKGROUNDEXTENT)(HTHEME hTheme,  HDC hdc,
		int iPartId, int iStateId, const RECT *pContentRect, 
		RECT *pExtentRect);
	static HRESULT __stdcall GetThemeBackgroundExtentFail(HTHEME hTheme,  HDC hdc,
		int iPartId, int iStateId, const RECT *pContentRect, 
		RECT *pExtentRect)
	{return E_FAIL;}

	typedef HRESULT(__stdcall *PFNGETTHEMEPARTSIZE)(HTHEME hTheme, HDC hdc, 
		int iPartId, int iStateId, RECT * pRect, enum THEMESIZE eSize,  SIZE *psz);
	static HRESULT __stdcall GetThemePartSizeFail(HTHEME, HDC, int, int, RECT *, enum THEMESIZE, SIZE *)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNGETTHEMETEXTEXTENT)(HTHEME hTheme, HDC hdc, 
		int iPartId, int iStateId, LPCWSTR pszText, int iCharCount, 
		DWORD dwTextFlags,  const RECT *pBoundingRect, 
		RECT *pExtentRect);
	static HRESULT __stdcall GetThemeTextExtentFail(HTHEME hTheme, HDC hdc, 
		int iPartId, int iStateId, LPCWSTR pszText, int iCharCount, 
		DWORD dwTextFlags,  const RECT *pBoundingRect, 
		RECT *pExtentRect)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNGETTHEMETEXTMETRICS)(HTHEME hTheme,  HDC hdc, 
		int iPartId, int iStateId,  TEXTMETRIC* ptm);
	static HRESULT __stdcall GetThemeTextMetricsFail(HTHEME hTheme,  HDC hdc, 
		int iPartId, int iStateId,  TEXTMETRIC* ptm)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNGETTHEMEBACKGROUNDREGION)(HTHEME hTheme,  HDC hdc,  
		int iPartId, int iStateId, const RECT *pRect,  HRGN *pRegion);
	static HRESULT __stdcall GetThemeBackgroundRegionFail(HTHEME hTheme,  HDC hdc,  
		int iPartId, int iStateId, const RECT *pRect,  HRGN *pRegion)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNHITTESTTHEMEBACKGROUND)(HTHEME hTheme,  HDC hdc, int iPartId, 
		int iStateId, DWORD dwOptions, const RECT *pRect,  HRGN hrgn, 
		POINT ptTest,  WORD *pwHitTestCode);
	static HRESULT __stdcall HitTestThemeBackgroundFail(HTHEME hTheme,  HDC hdc, int iPartId, 
		int iStateId, DWORD dwOptions, const RECT *pRect,  HRGN hrgn, 
		POINT ptTest,  WORD *pwHitTestCode)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNDRAWTHEMEEDGE)(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, 
		const RECT *pDestRect, UINT uEdge, UINT uFlags,   RECT *pContentRect);
	static HRESULT __stdcall DrawThemeEdgeFail(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, 
		const RECT *pDestRect, UINT uEdge, UINT uFlags,   RECT *pContentRect)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNDRAWTHEMEICON)(HTHEME hTheme, HDC hdc, int iPartId, 
		int iStateId, const RECT *pRect, HIMAGELIST himl, int iImageIndex);
	static HRESULT __stdcall DrawThemeIconFail(HTHEME hTheme, HDC hdc, int iPartId, 
		int iStateId, const RECT *pRect, HIMAGELIST himl, int iImageIndex)
	{return E_FAIL;}

	typedef BOOL (__stdcall *PFNISTHEMEPARTDEFINED)(HTHEME hTheme, int iPartId, 
		int iStateId);
	static BOOL __stdcall IsThemePartDefinedFail(HTHEME hTheme, int iPartId, 
		int iStateId)
	{return FALSE;}

	typedef BOOL (__stdcall *PFNISTHEMEBACKGROUNDPARTIALLYTRANSPARENT)(HTHEME hTheme, 
		int iPartId, int iStateId);
	static BOOL __stdcall IsThemeBackgroundPartiallyTransparentFail(HTHEME hTheme, 
		int iPartId, int iStateId)
	{return FALSE;}

	typedef HRESULT (__stdcall *PFNGETTHEMECOLOR)(HTHEME hTheme, int iPartId, 
		int iStateId, int iPropId,  COLORREF *pColor);
	static HRESULT __stdcall GetThemeColorFail(HTHEME hTheme, int iPartId, 
		int iStateId, int iPropId,  COLORREF *pColor)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNGETTHEMEMETRIC)(HTHEME hTheme,  HDC hdc, int iPartId, 
		int iStateId, int iPropId,  int *piVal);
	static HRESULT __stdcall GetThemeMetricFail(HTHEME hTheme,  HDC hdc, int iPartId, 
		int iStateId, int iPropId,  int *piVal)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNGETTHEMESTRING)(HTHEME hTheme, int iPartId, 
		int iStateId, int iPropId,  LPWSTR pszBuff, int cchMaxBuffChars);
	static HRESULT __stdcall GetThemeStringFail(HTHEME hTheme, int iPartId, 
		int iStateId, int iPropId,  LPWSTR pszBuff, int cchMaxBuffChars)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNGETTHEMEBOOL)(HTHEME hTheme, int iPartId, 
		int iStateId, int iPropId,  BOOL *pfVal);
	static HRESULT __stdcall GetThemeBoolFail(HTHEME hTheme, int iPartId, 
		int iStateId, int iPropId,  BOOL *pfVal)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNGETTHEMEINT)(HTHEME hTheme, int iPartId, 
		int iStateId, int iPropId,  int *piVal);
	static HRESULT __stdcall GetThemeIntFail(HTHEME hTheme, int iPartId, 
		int iStateId, int iPropId,  int *piVal)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNGETTHEMEENUMVALUE)(HTHEME hTheme, int iPartId, 
		int iStateId, int iPropId,  int *piVal);
	static HRESULT __stdcall GetThemeEnumValueFail(HTHEME hTheme, int iPartId, 
		int iStateId, int iPropId,  int *piVal)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNGETTHEMEPOSITION)(HTHEME hTheme, int iPartId, 
		int iStateId, int iPropId,  POINT *pPoint);
	static HRESULT __stdcall GetThemePositionFail(HTHEME hTheme, int iPartId, 
		int iStateId, int iPropId,  POINT *pPoint)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNGETTHEMEFONT)(HTHEME hTheme,  HDC hdc, int iPartId, 
		int iStateId, int iPropId,  LOGFONT *pFont);
	static HRESULT __stdcall GetThemeFontFail(HTHEME hTheme,  HDC hdc, int iPartId, 
		int iStateId, int iPropId,  LOGFONT *pFont)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNGETTHEMERECT)(HTHEME hTheme, int iPartId, 
		int iStateId, int iPropId,  RECT *pRect);
	static HRESULT __stdcall GetThemeRectFail(HTHEME hTheme, int iPartId, 
		int iStateId, int iPropId,  RECT *pRect)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNGETTHEMEMARGINS)(HTHEME hTheme,  HDC hdc, int iPartId, 
		int iStateId, int iPropId,  RECT *prc,  MARGINS *pMargins);
	static HRESULT __stdcall GetThemeMarginsFail(HTHEME hTheme,  HDC hdc, int iPartId, 
		int iStateId, int iPropId,  RECT *prc,  MARGINS *pMargins)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNGETTHEMEINTLIST)(HTHEME hTheme, int iPartId, 
		int iStateId, int iPropId,  INTLIST *pIntList);
	static HRESULT __stdcall GetThemeIntListFail(HTHEME hTheme, int iPartId, 
		int iStateId, int iPropId,  INTLIST *pIntList)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNGETTHEMEPROPERTYORIGIN)(HTHEME hTheme, int iPartId, 
		int iStateId, int iPropId,  enum PROPERTYORIGIN *pOrigin);
	static HRESULT __stdcall GetThemePropertyOriginFail(HTHEME hTheme, int iPartId, 
		int iStateId, int iPropId,  enum PROPERTYORIGIN *pOrigin)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNSETWINDOWTHEME)(HWND hwnd, LPCWSTR pszSubAppName, 
		LPCWSTR pszSubIdList);
	static HRESULT __stdcall SetWindowThemeFail(HWND hwnd, LPCWSTR pszSubAppName, 
		LPCWSTR pszSubIdList)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNGETTHEMEFILENAME)(HTHEME hTheme, int iPartId, 
		int iStateId, int iPropId,  LPWSTR pszThemeFileName, int cchMaxBuffChars);
	static HRESULT __stdcall GetThemeFilenameFail(HTHEME hTheme, int iPartId, 
		int iStateId, int iPropId,  LPWSTR pszThemeFileName, int cchMaxBuffChars)
	{return E_FAIL;}

	typedef COLORREF (__stdcall *PFNGETTHEMESYSCOLOR)(HTHEME hTheme, int iColorId);
	static COLORREF __stdcall GetThemeSysColorFail(HTHEME hTheme, int iColorId)
	{return RGB(255,255,255);}

	typedef HBRUSH (__stdcall *PFNGETTHEMESYSCOLORBRUSH)(HTHEME hTheme, int iColorId);
	static HBRUSH __stdcall GetThemeSysColorBrushFail(HTHEME hTheme, int iColorId)
	{return NULL;}

	typedef BOOL (__stdcall *PFNGETTHEMESYSBOOL)(HTHEME hTheme, int iBoolId);
	static BOOL __stdcall GetThemeSysBoolFail(HTHEME hTheme, int iBoolId)
	{return FALSE;}

	typedef int (__stdcall *PFNGETTHEMESYSSIZE)(HTHEME hTheme, int iSizeId);
	static int __stdcall GetThemeSysSizeFail(HTHEME hTheme, int iSizeId)
	{return 0;}

	typedef HRESULT (__stdcall *PFNGETTHEMESYSFONT)(HTHEME hTheme, int iFontId,  LOGFONT *plf);
	static HRESULT __stdcall GetThemeSysFontFail(HTHEME hTheme, int iFontId,  LOGFONT *plf)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNGETTHEMESYSSTRING)(HTHEME hTheme, int iStringId, 
		LPWSTR pszStringBuff, int cchMaxStringChars);
	static HRESULT __stdcall GetThemeSysStringFail(HTHEME hTheme, int iStringId, 
		LPWSTR pszStringBuff, int cchMaxStringChars)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNGETTHEMESYSINT)(HTHEME hTheme, int iIntId, int *piValue);
	static HRESULT __stdcall GetThemeSysIntFail(HTHEME hTheme, int iIntId, int *piValue)
	{return E_FAIL;}

	typedef BOOL (__stdcall *PFNISTHEMEACTIVE)();
	static BOOL __stdcall IsThemeActiveFail()
	{return FALSE;}

	typedef BOOL(__stdcall *PFNISAPPTHEMED)();
	static BOOL __stdcall IsAppThemedFail()
	{return FALSE;}

	typedef HTHEME (__stdcall *PFNGETWINDOWTHEME)(HWND hwnd);
	static HTHEME __stdcall GetWindowThemeFail(HWND hwnd)
	{return NULL;}

	typedef HRESULT (__stdcall *PFNENABLETHEMEDIALOGTEXTURE)(HWND hwnd, DWORD dwFlags);
	static HRESULT __stdcall EnableThemeDialogTextureFail(HWND hwnd, DWORD dwFlags)
	{return E_FAIL;}

	typedef BOOL (__stdcall *PFNISTHEMEDIALOGTEXTUREENABLED)(HWND hwnd);
	static BOOL __stdcall IsThemeDialogTextureEnabledFail(HWND hwnd)
	{return FALSE;}

	typedef DWORD (__stdcall *PFNGETTHEMEAPPPROPERTIES)();
	static DWORD __stdcall GetThemeAppPropertiesFail()
	{return 0;}

	typedef void (__stdcall *PFNSETTHEMEAPPPROPERTIES)(DWORD dwFlags);
	static void __stdcall SetThemeAppPropertiesFail(DWORD dwFlags)
	{return;}

	typedef HRESULT (__stdcall *PFNGETCURRENTTHEMENAME)(
		LPWSTR pszThemeFileName, int cchMaxNameChars, 
		LPWSTR pszColorBuff, int cchMaxColorChars,
		LPWSTR pszSizeBuff, int cchMaxSizeChars);
	static HRESULT __stdcall GetCurrentThemeNameFail(
		LPWSTR pszThemeFileName, int cchMaxNameChars, 
		LPWSTR pszColorBuff, int cchMaxColorChars,
		LPWSTR pszSizeBuff, int cchMaxSizeChars)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNGETTHEMEDOCUMENTATIONPROPERTY)(LPCWSTR pszThemeName,
		LPCWSTR pszPropertyName,  LPWSTR pszValueBuff, int cchMaxValChars);
	static HRESULT __stdcall GetThemeDocumentationPropertyFail(LPCWSTR pszThemeName,
		LPCWSTR pszPropertyName,  LPWSTR pszValueBuff, int cchMaxValChars)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNDRAWTHEMEPARENTBACKGROUND)(HWND hwnd, HDC hdc,  RECT* prc);
	static HRESULT __stdcall DrawThemeParentBackgroundFail(HWND hwnd, HDC hdc,  RECT* prc)
	{return E_FAIL;}

	typedef HRESULT (__stdcall *PFNENABLETHEMING)(BOOL fEnable);
	static HRESULT __stdcall EnableThemingFail(BOOL fEnable)
	{return E_FAIL;}
public:
	HTHEME OpenThemeData(HWND hwnd, LPCWSTR pszClassList);
	HRESULT CloseThemeData(HTHEME hTheme);
	HRESULT DrawThemeBackground(HTHEME hTheme, HDC hdc, 
		int iPartId, int iStateId, const RECT *pRect, const RECT *pClipRect);
	HRESULT DrawThemeText(HTHEME hTheme, HDC hdc, int iPartId, 
		int iStateId, LPCWSTR pszText, int iCharCount, DWORD dwTextFlags, 
		DWORD dwTextFlags2, const RECT *pRect);
	HRESULT GetThemeBackgroundContentRect(HTHEME hTheme,  HDC hdc, 
		int iPartId, int iStateId,  const RECT *pBoundingRect, 
		RECT *pContentRect);
	HRESULT GetThemeBackgroundExtent(HTHEME hTheme,  HDC hdc,
		int iPartId, int iStateId, const RECT *pContentRect, 
		RECT *pExtentRect);
	HRESULT GetThemePartSize(HTHEME hTheme, HDC hdc, 
		int iPartId, int iStateId, RECT * pRect, enum THEMESIZE eSize, SIZE *psz);
	HRESULT GetThemeTextExtent(HTHEME hTheme, HDC hdc, 
		int iPartId, int iStateId, LPCWSTR pszText, int iCharCount, 
		DWORD dwTextFlags,  const RECT *pBoundingRect, 
		RECT *pExtentRect);
	HRESULT GetThemeTextMetrics(HTHEME hTheme,  HDC hdc, 
		int iPartId, int iStateId,  TEXTMETRIC* ptm);
	HRESULT GetThemeBackgroundRegion(HTHEME hTheme,  HDC hdc,  
		int iPartId, int iStateId, const RECT *pRect,  HRGN *pRegion);
	HRESULT HitTestThemeBackground(HTHEME hTheme,  HDC hdc, int iPartId, 
		int iStateId, DWORD dwOptions, const RECT *pRect,  HRGN hrgn, 
		POINT ptTest,  WORD *pwHitTestCode);
	HRESULT DrawThemeEdge(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, 
		const RECT *pDestRect, UINT uEdge, UINT uFlags,   RECT *pContentRect);
	HRESULT DrawThemeIcon(HTHEME hTheme, HDC hdc, int iPartId, 
		int iStateId, const RECT *pRect, HIMAGELIST himl, int iImageIndex);
	BOOL IsThemePartDefined(HTHEME hTheme, int iPartId, 
		int iStateId);
	BOOL IsThemeBackgroundPartiallyTransparent(HTHEME hTheme, 
		int iPartId, int iStateId);
	HRESULT GetThemeColor(HTHEME hTheme, int iPartId, 
		int iStateId, int iPropId,  COLORREF *pColor);
	HRESULT GetThemeMetric(HTHEME hTheme,  HDC hdc, int iPartId, 
		int iStateId, int iPropId,  int *piVal);
	HRESULT GetThemeString(HTHEME hTheme, int iPartId, 
		int iStateId, int iPropId,  LPWSTR pszBuff, int cchMaxBuffChars);
	HRESULT GetThemeBool(HTHEME hTheme, int iPartId, 
		int iStateId, int iPropId,  BOOL *pfVal);
	HRESULT GetThemeInt(HTHEME hTheme, int iPartId, 
		int iStateId, int iPropId,  int *piVal);
	HRESULT GetThemeEnumValue(HTHEME hTheme, int iPartId, 
		int iStateId, int iPropId,  int *piVal);
	HRESULT GetThemePosition(HTHEME hTheme, int iPartId, 
		int iStateId, int iPropId,  POINT *pPoint);
	HRESULT GetThemeFont(HTHEME hTheme,  HDC hdc, int iPartId, 
		int iStateId, int iPropId,  LOGFONT *pFont);
	HRESULT GetThemeRect(HTHEME hTheme, int iPartId, 
		int iStateId, int iPropId,  RECT *pRect);
	HRESULT GetThemeMargins(HTHEME hTheme,  HDC hdc, int iPartId, 
		int iStateId, int iPropId,  RECT *prc,  MARGINS *pMargins);
	HRESULT GetThemeIntList(HTHEME hTheme, int iPartId, 
		int iStateId, int iPropId,  INTLIST *pIntList);
	HRESULT GetThemePropertyOrigin(HTHEME hTheme, int iPartId, 
		int iStateId, int iPropId,  enum PROPERTYORIGIN *pOrigin);
	HRESULT SetWindowTheme(HWND hwnd, LPCWSTR pszSubAppName, 
		LPCWSTR pszSubIdList);
	HRESULT GetThemeFilename(HTHEME hTheme, int iPartId, 
		int iStateId, int iPropId,  LPWSTR pszThemeFileName, int cchMaxBuffChars);
	COLORREF GetThemeSysColor(HTHEME hTheme, int iColorId);
	HBRUSH GetThemeSysColorBrush(HTHEME hTheme, int iColorId);
	BOOL GetThemeSysBool(HTHEME hTheme, int iBoolId);
	int GetThemeSysSize(HTHEME hTheme, int iSizeId);
	HRESULT GetThemeSysFont(HTHEME hTheme, int iFontId,  LOGFONT *plf);
	HRESULT GetThemeSysString(HTHEME hTheme, int iStringId, 
		LPWSTR pszStringBuff, int cchMaxStringChars);
	HRESULT GetThemeSysInt(HTHEME hTheme, int iIntId, int *piValue);
	BOOL IsThemeActive();
	BOOL IsAppThemed();	
	HTHEME GetWindowTheme(HWND hwnd);
	HRESULT EnableThemeDialogTexture(HWND hwnd, DWORD dwFlags);
	BOOL IsThemeDialogTextureEnabled(HWND hwnd);
	DWORD GetThemeAppProperties();
	void SetThemeAppProperties(DWORD dwFlags);
	HRESULT GetCurrentThemeName(
		LPWSTR pszThemeFileName, int cchMaxNameChars, 
		LPWSTR pszColorBuff, int cchMaxColorChars,
		LPWSTR pszSizeBuff, int cchMaxSizeChars);
	HRESULT GetThemeDocumentationProperty(LPCWSTR pszThemeName,
		LPCWSTR pszPropertyName,  LPWSTR pszValueBuff, int cchMaxValChars);
	HRESULT DrawThemeParentBackground(HWND hwnd, HDC hdc,  RECT* prc);
	HRESULT EnableTheming(BOOL fEnable);
public:
	CVisualStylesXP(void);
	~CVisualStylesXP(void);
};

extern CVisualStylesXP g_xpStyle;

#endif