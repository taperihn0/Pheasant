#pragma once

/* Instruction sets are iterative, that is
*  they are build on top of each other.
*  I safely assume I can use instructions from older standards.
*/

#ifdef PHEASANT_SIMD_AVX512
#  define PHS_SIMD_AVX512
#  define PHEASANT_SIMD_AVX2
#endif

#ifdef PHEASANT_SIMD_AVX2
#  define PHS_SIMD_AVX2
#  define PHEASANT_SIMD_AVX
#endif

#ifdef PHEASANT_SIMD_AVX
#  define PHS_SIMD_AVX
#  define PHEASANT_SIMD_SSE4_2
#endif

#ifdef PHEASANT_SIMD_SSE4_2
#  define PHS_SIMD_SSE4_2
#  define PHEASANT_SIMD_SSE4_1
#endif

#ifdef PHEASANT_SIMD_SSE4_1
#  define PHS_SIMD_SSE4_1
#  define PHEASANT_SIMD_SSSE3
#endif

#ifdef PHEASANT_SIMD_SSSE3
#  define PHS_SIMD_SSSE3
#  define PHEASANT_SIMD_SSE3
#endif

#ifdef PHEASANT_SIMD_SSE3
#  define PHS_SIMD_SSE3
#  define PHEASANT_SIMD_SSE2
#endif

#ifdef PHEASANT_SIMD_SSE2
#  define PHS_SIMD_SSE2
#endif

#ifdef PHEASANT_FORCE_PURE
#  define PHS_FORCE_PURE
#endif

#ifndef PHS_FORCE_PURE

#include "defines.h"

#ifdef PHS_SIMD_AVX
#  include <immintrin.h>   // AVX, AVX2, AVX-512, BMI, FMA, etc.
#elif defined(PHS_SIMD_SSE4_2)
#  include <nmmintrin.h>   // SSE4.2
#elif defined(PHS_SIMD_SSE4_1)
#  include <smmintrin.h>   // SSE4.1
#elif defined(PHS_SIMD_SSSE3)
#  include <tmmintrin.h>   // SSSE3
#elif defined(PHS_SIMD_SSE3)
#  include <pmmintrin.h>   // SSE3
#elif defined(PHS_SIMD_SSE2)
#  include <emmintrin.h>   // SSE2
#elif defined(PHS_SIMD_SEE)
#  include <xmmintrin.h>   // SSE
#endif

#endif // PHS_FORCE_PURE
