#pragma once

#include "precompile.h"
#include "common.h"

namespace Phs
{

bool Log::_initialized = false;

void Log::init()
{
   std::cout.sync_with_stdio(0);
   _initialized = true;
}

template <typename... Ts>
void Log::message(Log::messageLevel lvl, Ts&&... args)
{
   PHS_ASSERT(_initialized);

   const size_t msgval = static_cast<size_t>(lvl) - 1;

   PHS_ASSERT(msgval < LvlCount);

   std::cout << LevelStr[msgval] << ": ";

   std::string format = getNthArgument<0>(args...);
   print_message_queue(std::move(format), std::forward<Ts>(args)...);

   std::cout << '\n';
}

template <std::size_t N, typename... Ts>
PHS_INLINE void Log::print_message_queue(std::string format, Ts&&... queue)
{
   PHS_ASSERT(_initialized);
   PHS_STATIC_ASSERT(N > 0);

   const size_t pos = format.find("{}");
   std::cout << format.substr(0, pos);

   if (pos == std::string::npos)
      return;

   if constexpr (N < sizeof...(queue)) {
      std::cout << getNthArgument<N>(std::forward<Ts>(queue)...);
      std::string tail = format.substr(pos + 2);
      print_message_queue<N + 1>(std::move(tail), std::forward<Ts>(queue)...);
   }
   else {
      PHS_ASSERT_LOG(false, "Too little arguments for their placeholders provided.");
      return;
   }
}

} // namespace Phs
