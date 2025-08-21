#pragma once

#include "precompile.h"
#include "types.h"
#include "assert.h"

namespace Phs
{

class PHEASANT_API Log
{
public:
   static void init();

   enum messageLevel : uint8_t
   {
      MSG_TRACE = 1,
      MSG_MIN = MSG_TRACE,
      MSG_DEBUG = 2,
      MSG_INFO = 3,
      MSG_WARN = 4,
      MSG_ERROR = 5,
      MSG_FATAL = 6,
      MSG_MAX = MSG_FATAL,
   };

   PHS_STATIC_ASSERT_LOG(MSG_MIN == 1, "MSG_MAX is not equal to MSG_COUNT value.");

   template <typename... Ts>
   static void message(messageLevel lvl, Ts&&... args);
private:
   template <size_t N = 1, typename... Ts>
   static void print_message_queue(std::string format, Ts&&... queue);

   static constexpr size_t LvlCount = MSG_MAX;

   static constexpr std::string_view LevelStr[LvlCount] =
   {
      "[TRACE]",
      "[DEBUG]",
      "[INFO]",
      "[WARN]",
      "[ERROR]",
      "[FATAL]"
   };

   static bool _initialized;
};

}

#define PHS_LOG_TRACE(...) ::Log::message(::Log::MSG_TRACE, __VA_ARGS__)
#define PHS_LOG_DEBUG(...) ::Log::message(::Log::MSG_DEBUG, __VA_ARGS__)
#define PHS_LOG_INFO(...)  ::Log::message(::Log::MSG_INFO,  __VA_ARGS__)
#define PHS_LOG_WARN(...)  ::Log::message(::Log::MSG_WARN,  __VA_ARGS__)
#define PHS_LOG_ERROR(...) ::Log::message(::Log::MSG_ERROR, __VA_ARGS__)
#define PHS_LOG_FATAL(...) ::Log::message(::Log::MSG_FATAL, __VA_ARGS__)

#include "log.inl"
