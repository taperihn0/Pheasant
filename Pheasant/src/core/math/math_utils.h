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

static constexpr float64_t __Epsilon64f = 1e-6_f64;

template <typename T>
constexpr PHS_INLINE T abs(T a)
{
   PHS_STATIC_ASSERT(is_numeric<T>);
   return a < 0 ? -a : a;
}

constexpr PHS_INLINE bool approxEqual64f(float64_t a, float64_t b)
{
   const float64_t diff = abs(a - b);
   return diff <= __Epsilon64f;
}

// TODO: make them compile-time
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

template <typename T>
PHS_INLINE T sqrt(float64_t x)
{
   PHS_STATIC_ASSERT(is_numeric<T>);
   return std::sqrt(x);
}

using dim_int_t = uint;

} // namespace Phs
