#pragma once

#define NONE_TOKEN  

#ifdef PHEASANT_BUILD_EXPORT
#	if defined(PHEASANT_PLATFORM_WINDOWS)
#		define PHEASANT_API __declspec(dllexport)
#	elif defined(PHEASANT_PLATFORM_LINUX)
#		define PHEASANT_API __attribute__((visibility("default")))
#  elif defined(PHEASANT_PLATFORM_MACOS)
#     error "MacOS system is not supported so far."
#	endif
#else
#	if defined(PHEASANT_PLATFORM_WINDOWS)
#		define PHEASANT_API __declspec(dllimport)
#  elif defined(PHEASANT_PLATFORM_LINUX)
#		define PHEASANT_API NONE_TOKEN
#  elif defined(PHEASANT_PLATFORM_MACOS)
#     error "MacOS system is not supported so far."
#  endif
#endif

#ifdef PHEASANT_PLATFORM_WINDOWS
#  define PHS_OS_WINDOWS
#elif defined(PHEASANT_PLATFORM_LINUX)
#  define PHS_OS_LINUX
#elif defined(PHEASANT_PLATFORM_MACOS)
#  define PHS_OS_MACOS
#endif

#ifdef PHEASANT_DEBUG
#  define PHS_DEBUG
#endif

#ifdef PHEASANT_RELEASE
#  define PHS_RELEASE
#endif

#if  __cplusplus >= 202002L
#  define PHEASANT_STANDARD_20
#  define PHS_STANDARD_20
#elif __cplusplus >= 201702L
#  define PHEASANT_STANDARD_17
#  define PHS_STANDARD_17
#else
#  error "C++ standard not defined"
#endif

#if defined(_MSC_VER)
#  define PHS_INLINE              inline 
#  define PHS_FORCEINLINE		    __forceinline
#  define PHS_LAMBDA_FORCEINLINE  [[msvc::forceinline]] 
#  define PHS_NODISCARD           [[nodiscard]]
#elif defined(__GNUG__)
#  define PHS_INLINE				    inline
#  define PHS_FORCEINLINE		    __attribute__((always_inline))
#  define PHS_LAMBDA_FORCEINLINE  NONE_TOKEN
#  define PHS_NODISCARD           [[nodiscard]]
#endif

#define PHS_NORETURN              [[noreturn]]
#define PHS_UNUSED                [[maybe_unused]]
#define PHS_FALLTHROUGH           [[fallthrough]]

#if defined(PHS_STANDARD_20)
#  define PHS_UNLIKELY            [[unlikely]]
#else
#  define PHS_UNLIKELY
#endif

#ifdef ARCHITECTURE_64
#  define CACHELINE_SIZE 64
#else
#  error "Only 64-bit architecture supported"
#endif

#ifdef _MSC_VER
// Warning: 'Phs::Log::LevelStr': 'std::basic_string_view<char,std::char_traits<char>>' needs to have dll-interface to be used by clients of 'Phs::Log'
// Phs::Log::LevelStr is already private, so safely ignore that warning.
#pragma warning(disable: 4251)
// Warning : 'extern ' : ignored on left of 'Phs::Event<Code>::WindowPosParams' when no variable is declared
#pragma warning(disable: 4091)
#endif

// Check for language extensions.
// Language extensions are turned on by default under MSVC and GCC
#ifdef _MSC_VER
#  define PHS_EXTENSIONS
#elif defined(__GNUG__)
#  define PHS_EXTENSIONS
#endif

// Extension features
#ifdef PHS_EXTENSIONS
#  define PHS_USE_ANONYMOUS_STRUCT
#endif

#define PHS_MATH_USE_NOEXCEPT 1
