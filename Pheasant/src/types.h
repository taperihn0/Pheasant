#pragma once

#include "defines.h"
#include "assert.h"

#include <cstdint>
#include <limits>

// Assert IEEE Standard is implemented
PHS_STATIC_ASSERT(std::numeric_limits<float>::is_iec559);

using float32_t = float;
using float64_t = double;

using byte = uint8_t;

using longlong = long long;
using ulonglong = unsigned long long;

template <typename T>
constexpr PHS_INLINE T maxof() 
{
   PHS_STATIC_ASSERT(std::is_floating_point_v<T> or std::is_integral_v<T>);
   return std::numeric_limits<T>::max();
}

template <typename T>
constexpr PHS_INLINE T minof() 
{
   PHS_STATIC_ASSERT(std::is_floating_point_v<T> or std::is_integral_v<T>);
   return std::numeric_limits<T>::lowest();
}
