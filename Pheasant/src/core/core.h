#pragma once

#ifdef PHEASANT_BUILD_EXPORT
#	ifdef PHEASANT_PLATFORM_WINDOWS
#		define PHEASANT_API __declspec(dllexport)
#	else // Linux system by default, MacOS is not handled yet
#		define PHEASANT_API __attribute__((visibility("default")))
#	endif
#else
#	ifdef PHEASANT_PLATFORM_WINDOWS
#		define PHEASANT_API __declspec(dllimport)
#	else // Linux by default
#		define PHEASANT_API 
#	endif
#endif
