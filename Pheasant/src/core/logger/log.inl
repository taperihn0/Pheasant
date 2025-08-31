#pragma once

#include "precompile.h"
#include "common.h"

namespace Phs
{

#if PHS_FLUSH_OUTPUT
#  define PHS_LOG_FLUSH_SPECIFIER std::flush
#else
#  define PHS_LOG_FLUSH_SPECIFIER NONE_TOKEN
#endif

template <typename... Ts>
void Log::message(Log::messageLevel lvl, Ts&&... args)
{
   PHS_ASSERT(_initialized);
   PHS_STATIC_ASSERT(sizeof...(args) < _ArgumentLimit);

   const size_t msgval = static_cast<size_t>(lvl) - 1;

   PHS_ASSERT(msgval < _LevelCount);

   std::cout << _ANSIColor[msgval] << _LevelStr[msgval] << ": ";

   std::string format = getNthArgument<0>(args...);
   print_message_queue(std::move(format), std::forward<Ts>(args)...);

   std::cout << _ANSIColorReset << PHS_LOG_FLUSH_SPECIFIER << '\n';
}

template <typename... Ts>
void Log::fullInfoMessage(const char* file, uint line, const char* func, Ts&&... args)
{
   message(MSG_FATAL, std::forward<Ts>(args)...);
   message(MSG_FATAL, "file {}, line {}", file, line);
   message(MSG_FATAL, "func {}", func);
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

   if constexpr (N < sizeof...(queue)) 
   {
      std::cout << getNthArgument<N>(std::forward<Ts>(queue)...);
      std::string tail = format.substr(pos + 2);
      print_message_queue<N + 1>(std::move(tail), std::forward<Ts>(queue)...);
   }
   else 
   {
      PHS_ASSERT_LOG(false, "Too little arguments for their placeholders provided.");
      return;
   }
}

} // namespace Phs
