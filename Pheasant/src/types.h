#pragma once

#include "defines.h"
#include "assert.h"
#include <cstdint>
#include <limits>
#include <uchar.h>

// Some libraries defines that, so undef them
#undef max
#undef min

namespace Phs
{

template <typename T1, typename T2>
constexpr PHS_INLINE bool isSameType() {
   return std::is_same_v<std::remove_const<std::remove_reference<T1>>, 
                         std::remove_const<std::remove_reference<T2>>>;
};

// Assert IEEE Standard is implemented
PHS_STATIC_ASSERT(std::numeric_limits<float>::is_iec559);

// As IEEE is checked, these types exactly maps their size.
using float32_t = float;
using float64_t = double;

// Define some handy aliases
using byte      = uint8_t;
using ll        = long long;
using ull       = unsigned long long;
using uint      = unsigned int;

static constexpr uint8_t operator"" _u8(uintmax_t v)
{
   return static_cast<uint8_t>(v);
}

static constexpr uint16_t operator"" _u16(uintmax_t v)
{
   return static_cast<uint16_t>(v);
}

static constexpr uint32_t operator"" _u32(uintmax_t v)
{
   return static_cast<uint32_t>(v);
}

static constexpr uint64_t operator"" _u64(uintmax_t v)
{
   return static_cast<uint64_t>(v);
}

static constexpr int8_t operator"" _i8(uintmax_t v)
{
   return static_cast<int8_t>(v);
}

static constexpr int16_t operator"" _i16(uintmax_t v)
{
   return static_cast<int16_t>(v);
}

static constexpr int32_t operator"" _i32(uintmax_t v)
{
   return static_cast<int32_t>(v);
}

static constexpr int64_t operator"" _i64(uintmax_t v)
{
   return static_cast<int64_t>(v);
}

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

} // namespace Phs
