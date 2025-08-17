#pragma once

#if defined(PHS_BUILD_EXPORT)
#	define PHEASANT_API __declspec(dllexport)
#else
#	define PHEASANT_API __declspec(dllimport)
#endif
