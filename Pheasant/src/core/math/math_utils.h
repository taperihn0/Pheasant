#pragma once

#include "common.h"
#include "types.h"
#include "precompile.h"
#include <cmath>

#if PHS_MATH_USE_NOEXCEPT
#  define PHS_MATH_NOEXCEPT noexcept
#else
#  define PHS_MATH_NOEXCEPT NONE_TOKEN
#endif

namespace Phs
{

PHS_INLINE float32_t round32f(float32_t x)
{
   return std::round(x);
}

PHS_INLINE float64_t round64f(float64_t x)
{
   return std::round(x);
}

template <typename T>
PHS_FORCEINLINE T sq(T x) PHS_MATH_NOEXCEPT
{
   PHS_STATIC_ASSERT(is_numeric<T>);
   return x * x;
}

using dim_int_t = uint;

} // namespace Phs
