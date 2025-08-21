#pragma once

#include "defines.h"

namespace Phs {

template<std::size_t N, typename... Ts>
decltype(auto) getNthArgument(Ts&&... args)
{
   PHS_STATIC_ASSERT(N < sizeof...(args));
   return std::get<N>(std::forward_as_tuple(std::forward<Ts>(args)...));
}

} // namespace Phs
