#pragma once

#include "defines.h"
#include "precompile.h"

#ifdef PHS_DEBUG
#  define PHS_ASSERT_ENABLE
#endif

#ifdef PHS_ASSERT_ENABLE

#ifdef PHS_OS_WINDOWS
#	define PHS_DEBUG_BREAK() __debugbreak()
#else
#	define PHS_DEBUG_BREAK() __builtin_trap()
#endif

PHS_INLINE bool failedAssertion(std::string_view file, std::string_view text, int line) 
{
	std::cout << "\nAssertion failed: " << text << " file " << file << " line " << line << std::endl;
	PHS_DEBUG_BREAK();
	return true;
}

#define PHS_ASSERT(s)						(void)((s) or failedAssertion(__FILE__, "Runtime assertion failed", __LINE__))
#define PHS_ASSERT_LOG(s, msg)			(void)((s) or failedAssertion(__FILE__, msg, __LINE__))
#define PHS_STATIC_ASSERT(s)				static_assert(s)
#define PHS_STATIC_ASSERT_LOG(s, msg)	static_assert(s, msg)

#else // Assertions not specified.

#define PHS_ASSERT(s)						NONE_TOKEN
#define PHS_ASSERT_LOG(s, msg)			NONE_TOKEN
#define PHS_STATIC_ASSERT(s)				NONE_TOKEN
#define PHS_STATIC_ASSERT_LOG(s, msg)	NONE_TOKEN

#endif // PHS_ASSERT_ENABLE
