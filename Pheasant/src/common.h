#pragma once

#include "types.h"

#ifndef __PRETTY_FUNCTION__
#  ifdef _MSC_VER
#     define __PRETTY_FUNCTION__ __FUNCSIG__
#  else
#     define __PRETTY_FUNCTION__ __func__
#  endif
#endif

namespace Phs {

template<std::size_t N, typename... Ts>
decltype(auto) getNthArgument(Ts&&... args)
{
   PHS_STATIC_ASSERT(N < sizeof...(args));
   return std::get<N>(std::forward_as_tuple(std::forward<Ts>(args)...));
}

// Returns a mask with only one bit set with an offset equal to shift
constexpr PHS_INLINE uint64_t shiftbit(uint8_t shift) {
   return 1_u64 << shift;
}

// Returns a mask containing only the lowest set bit in mask
constexpr PHS_INLINE uint64_t onebit(int64_t mask) {
   return static_cast<uint64_t>(mask & -mask);
}

} // namespace Phs
