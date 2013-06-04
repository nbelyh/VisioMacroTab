

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Tue Jun 04 21:03:07 2013
 */
/* Compiler settings for .\AddIn.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __AddIn_i_h__
#define __AddIn_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___IScriptSiteContext_FWD_DEFINED__
#define ___IScriptSiteContext_FWD_DEFINED__
typedef interface _IScriptSiteContext _IScriptSiteContext;
#endif 	/* ___IScriptSiteContext_FWD_DEFINED__ */


#ifndef __ICallbackInterface_FWD_DEFINED__
#define __ICallbackInterface_FWD_DEFINED__
typedef interface ICallbackInterface ICallbackInterface;
#endif 	/* __ICallbackInterface_FWD_DEFINED__ */


#ifndef __Connect_FWD_DEFINED__
#define __Connect_FWD_DEFINED__

#ifdef __cplusplus
typedef class Connect Connect;
#else
typedef struct Connect Connect;
#endif /* __cplusplus */

#endif 	/* __Connect_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __VisioMacroTabAddin_LIBRARY_DEFINED__
#define __VisioMacroTabAddin_LIBRARY_DEFINED__

/* library VisioMacroTabAddin */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_VisioMacroTabAddin;

#ifndef ___IScriptSiteContext_INTERFACE_DEFINED__
#define ___IScriptSiteContext_INTERFACE_DEFINED__

/* interface _IScriptSiteContext */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID__IScriptSiteContext;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("03B2AC65-F984-4d00-ACB3-B7580EF1D56C")
    _IScriptSiteContext : public IDispatch
    {
    public:
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Application( 
            /* [retval][out] */ IDispatch **pResult) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_ActiveDocument( 
            /* [retval][out] */ IDispatch **pResult) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_ActivePage( 
            /* [retval][out] */ IDispatch **pResult) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct _IScriptSiteContextVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IScriptSiteContext * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IScriptSiteContext * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IScriptSiteContext * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IScriptSiteContext * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IScriptSiteContext * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IScriptSiteContext * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IScriptSiteContext * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_Application )( 
            _IScriptSiteContext * This,
            /* [retval][out] */ IDispatch **pResult);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_ActiveDocument )( 
            _IScriptSiteContext * This,
            /* [retval][out] */ IDispatch **pResult);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE *get_ActivePage )( 
            _IScriptSiteContext * This,
            /* [retval][out] */ IDispatch **pResult);
        
        END_INTERFACE
    } _IScriptSiteContextVtbl;

    interface _IScriptSiteContext
    {
        CONST_VTBL struct _IScriptSiteContextVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IScriptSiteContext_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _IScriptSiteContext_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _IScriptSiteContext_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _IScriptSiteContext_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _IScriptSiteContext_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _IScriptSiteContext_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _IScriptSiteContext_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define _IScriptSiteContext_get_Application(This,pResult)	\
    ( (This)->lpVtbl -> get_Application(This,pResult) ) 

#define _IScriptSiteContext_get_ActiveDocument(This,pResult)	\
    ( (This)->lpVtbl -> get_ActiveDocument(This,pResult) ) 

#define _IScriptSiteContext_get_ActivePage(This,pResult)	\
    ( (This)->lpVtbl -> get_ActivePage(This,pResult) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ___IScriptSiteContext_INTERFACE_DEFINED__ */


#ifndef __ICallbackInterface_INTERFACE_DEFINED__
#define __ICallbackInterface_INTERFACE_DEFINED__

/* interface ICallbackInterface */
/* [unique][dual][uuid][object] */ 


EXTERN_C const IID IID_ICallbackInterface;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("76973C5D-E651-4f97-A90F-613AAC31933B")
    ICallbackInterface : public IDispatch
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE OnRibbonButtonClicked( 
            /* [in] */ IDispatch *RibbonControl) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE OnRibbonLoad( 
            /* [in] */ IDispatch *disp) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE OnRibbonLoadImage( 
            /* [in] */ BSTR pbstrImageId,
            /* [retval][out] */ IPictureDisp **ppdispImage) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE IsRibbonButtonEnabled( 
            /* [in] */ IDispatch *RibbonControl,
            /* [retval][out] */ VARIANT_BOOL *pResult) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE IsRibbonButtonVisible( 
            /* [in] */ IDispatch *RibbonControl,
            /* [retval][out] */ VARIANT_BOOL *pResult) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetRibbonLabel( 
            /* [in] */ IDispatch *pControl,
            /* [retval][out] */ BSTR *pbstrLabel) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE OnRibbonCheckboxClicked( 
            /* [in] */ IDispatch *pControl,
            /* [in] */ VARIANT_BOOL *pvarfPressed) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE IsRibbonButtonPressed( 
            /* [in] */ IDispatch *RibbonControl,
            /* [retval][out] */ VARIANT_BOOL *pResult) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICallbackInterfaceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICallbackInterface * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICallbackInterface * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICallbackInterface * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICallbackInterface * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICallbackInterface * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICallbackInterface * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICallbackInterface * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *OnRibbonButtonClicked )( 
            ICallbackInterface * This,
            /* [in] */ IDispatch *RibbonControl);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *OnRibbonLoad )( 
            ICallbackInterface * This,
            /* [in] */ IDispatch *disp);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *OnRibbonLoadImage )( 
            ICallbackInterface * This,
            /* [in] */ BSTR pbstrImageId,
            /* [retval][out] */ IPictureDisp **ppdispImage);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *IsRibbonButtonEnabled )( 
            ICallbackInterface * This,
            /* [in] */ IDispatch *RibbonControl,
            /* [retval][out] */ VARIANT_BOOL *pResult);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *IsRibbonButtonVisible )( 
            ICallbackInterface * This,
            /* [in] */ IDispatch *RibbonControl,
            /* [retval][out] */ VARIANT_BOOL *pResult);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetRibbonLabel )( 
            ICallbackInterface * This,
            /* [in] */ IDispatch *pControl,
            /* [retval][out] */ BSTR *pbstrLabel);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *OnRibbonCheckboxClicked )( 
            ICallbackInterface * This,
            /* [in] */ IDispatch *pControl,
            /* [in] */ VARIANT_BOOL *pvarfPressed);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *IsRibbonButtonPressed )( 
            ICallbackInterface * This,
            /* [in] */ IDispatch *RibbonControl,
            /* [retval][out] */ VARIANT_BOOL *pResult);
        
        END_INTERFACE
    } ICallbackInterfaceVtbl;

    interface ICallbackInterface
    {
        CONST_VTBL struct ICallbackInterfaceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICallbackInterface_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICallbackInterface_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICallbackInterface_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICallbackInterface_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ICallbackInterface_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ICallbackInterface_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ICallbackInterface_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ICallbackInterface_OnRibbonButtonClicked(This,RibbonControl)	\
    ( (This)->lpVtbl -> OnRibbonButtonClicked(This,RibbonControl) ) 

#define ICallbackInterface_OnRibbonLoad(This,disp)	\
    ( (This)->lpVtbl -> OnRibbonLoad(This,disp) ) 

#define ICallbackInterface_OnRibbonLoadImage(This,pbstrImageId,ppdispImage)	\
    ( (This)->lpVtbl -> OnRibbonLoadImage(This,pbstrImageId,ppdispImage) ) 

#define ICallbackInterface_IsRibbonButtonEnabled(This,RibbonControl,pResult)	\
    ( (This)->lpVtbl -> IsRibbonButtonEnabled(This,RibbonControl,pResult) ) 

#define ICallbackInterface_IsRibbonButtonVisible(This,RibbonControl,pResult)	\
    ( (This)->lpVtbl -> IsRibbonButtonVisible(This,RibbonControl,pResult) ) 

#define ICallbackInterface_GetRibbonLabel(This,pControl,pbstrLabel)	\
    ( (This)->lpVtbl -> GetRibbonLabel(This,pControl,pbstrLabel) ) 

#define ICallbackInterface_OnRibbonCheckboxClicked(This,pControl,pvarfPressed)	\
    ( (This)->lpVtbl -> OnRibbonCheckboxClicked(This,pControl,pvarfPressed) ) 

#define ICallbackInterface_IsRibbonButtonPressed(This,RibbonControl,pResult)	\
    ( (This)->lpVtbl -> IsRibbonButtonPressed(This,RibbonControl,pResult) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICallbackInterface_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_Connect;

#ifdef __cplusplus

class DECLSPEC_UUID("D62269B9-72CD-4ae9-BD41-B803A832B6F9")
Connect;
#endif
#endif /* __VisioMacroTabAddin_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


