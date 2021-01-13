#ifndef XT_CONFIG_H
#define XT_CONFIG_H

/**
* \file XTConfig.h
*
* \author Bin Deng (bdeng@xtal-tech.com)
*
* \brief  Provide a manager class for all xt configurations.
*
* \description
*	Designed for managing all xt configurations.
*/
//
// Some include files we need almost everywhere
//
#include <cerrno>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <map>

//#include <boost/system/error_code.hpp>

//
// Compiler extensions to export and import symbols: see the documentation 
// for Visual C++, Solaris Studio and HP aC++.
//
#if (defined(_MSC_VER) && !defined(ICE_STATIC_LIBS)) || \
    (defined(__HP_aCC) && defined(__HP_WINDLL))
#   define XT_DECLSPEC_EXPORT __declspec(dllexport)
#   define XT_DECLSPEC_IMPORT __declspec(dllimport)
#   define XT_HAS_DECLSPEC_IMPORT_EXPORT
#elif defined(__SUNPRO_CC)
#   define XT_DECLSPEC_EXPORT __global
#   define XT_DECLSPEC_IMPORT /**/
#else
#   define XT_DECLSPEC_EXPORT /**/
#   define XT_DECLSPEC_IMPORT /**/
#endif

//#ifndef XT_API
//#   ifdef XT_API_EXPORTS
//#       define XT_API XT_DECLSPEC_EXPORT
//#    else
//#       define XT_API XT_DECLSPEC_IMPORT
//#    endif
//#endif

#ifndef XT_COMMON_API
#   ifdef XT_COMMON_API_EXPORTS
#       define XT_COMMON_API XT_DECLSPEC_EXPORT
#    else
#       define XT_COMMON_API XT_DECLSPEC_IMPORT
#    endif
#endif

#ifndef XT_PLUGIN_API
#   ifdef XT_PLUGIN_API_EXPORTS
#       define XT_PLUGIN_API XT_DECLSPEC_EXPORT
#    else
#       define XT_PLUGIN_API XT_DECLSPEC_IMPORT
#    endif
#endif

#ifndef XT_SHARED_API
#   ifdef XT_SHARED_API_EXPORTS
#       define XT_SHARED_API XT_DECLSPEC_EXPORT
#    else
#       define XT_SHARED_API XT_DECLSPEC_IMPORT
#    endif
#endif

////////////////
#ifndef XT_BROKER_API
#   ifdef XT_BROKER_API_EXPORTS
#       define XT_BROKER_API XT_DECLSPEC_EXPORT
#    else
#       define XT_BROKER_API XT_DECLSPEC_IMPORT
#    endif
#endif


#ifndef XT_CTP_API
#   ifdef XT_CTP_API_EXPORTS
#       define XT_CTP_API XT_DECLSPEC_EXPORT
#    else
#       define XT_CTP_API XT_DECLSPEC_IMPORT
#    endif
#endif

#ifndef XT_DFITC_API
#   ifdef XT_DFITC_API_EXPORTS
#       define XT_DFITC_API XT_DECLSPEC_EXPORT
#    else
#       define XT_DFITC_API XT_DECLSPEC_IMPORT
#    endif
#endif

#ifndef XT_DFITCSEC_API
#   ifdef XT_DFITCSEC_API_EXPORTS
#       define XT_DFITCSEC_API XT_DECLSPEC_EXPORT
#    else
#       define XT_DFITCSEC_API XT_DECLSPEC_IMPORT
#    endif
#endif

#ifndef XT_EPOLARSTAR_API
#   ifdef XT_EPOLARSTAR_API_EXPORTS
#       define XT_EPOLARSTAR_API XT_DECLSPEC_EXPORT
#    else
#       define XT_EPOLARSTAR_API XT_DECLSPEC_IMPORT
#    endif
#endif

#ifndef XT_ESUNNY3_API
#   ifdef XT_ESUNNY3_API_EXPORTS
#       define XT_ESUNNY3_API XT_DECLSPEC_EXPORT
#    else
#       define XT_ESUNNY3_API XT_DECLSPEC_IMPORT
#    endif
#endif

#ifndef XT_ESUNNY8_API
#   ifdef XT_ESUNNY8_API_EXPORTS
#       define XT_ESUNNY8_API XT_DECLSPEC_EXPORT
#    else
#       define XT_ESUNNY8_API XT_DECLSPEC_IMPORT
#    endif
#endif

#ifndef XT_ESUNNY9_API
#   ifdef XT_ESUNNY9_API_EXPORTS
#       define XT_ESUNNY9_API XT_DECLSPEC_EXPORT
#    else
#       define XT_ESUNNY9_API XT_DECLSPEC_IMPORT
#    endif
#endif

#ifndef XT_IB_API
#   ifdef XT_IB_API_EXPORTS
#       define XT_IB_API XT_DECLSPEC_EXPORT
#    else
#       define XT_IB_API XT_DECLSPEC_IMPORT
#    endif
#endif

#ifndef XT_WEB_API
#   ifdef XT_WEB_API_EXPORTS
#       define XT_WEB_API XT_DECLSPEC_EXPORT
#    else
#       define XT_WEB_API XT_DECLSPEC_IMPORT
#    endif
#endif

#ifndef XT_XTP_API
#   ifdef XT_XTP_API_EXPORTS
#       define XT_XTP_API XT_DECLSPEC_EXPORT
#    else
#       define XT_XTP_API XT_DECLSPEC_IMPORT
#    endif
#endif


#ifndef XT_INSTRSTRAT_API
#   ifdef XT_INSTRSTRAT_API_EXPORTS
#       define XT_INSTRSTRAT_API XT_DECLSPEC_EXPORT
#    else
#       define XT_INSTRSTRAT_API XT_DECLSPEC_IMPORT
#    endif
#endif

#ifndef XT_STRAT_API
#   ifdef XT_STRAT_API_EXPORTS
#       define XT_STRAT_API XT_DECLSPEC_EXPORT
#    else
#       define XT_STRAT_API XT_DECLSPEC_IMPORT
#    endif
#endif

#endif