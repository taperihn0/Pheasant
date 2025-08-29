#pragma once

#include "precompile.h"
#include "types.h"

/* Sets line buffering.
*  It is rather slow, but useful for DEBUG builds
*  to obtain accurate information synchronized with other instructions.
*  For more efficient output set it to zero.
*/
#define PHS_FLUSH_OUTPUT 1

namespace Phs
{

/* Main static logger.
*  Its static methods are used rather internally - 
*  external use of this class is done via macro defined below.
*/
class PHEASANT_API Log
{
public:
   Log() = delete;

   enum messageLevel : uint8_t
   {
      MSG_TRACE = 1,
      MSG_MIN   = MSG_TRACE,
      MSG_DEBUG = 2,
      MSG_INFO  = 3,
      MSG_WARN  = 4,
      MSG_ERROR = 5,
      MSG_FATAL = 6,
      MSG_MAX   = MSG_FATAL,
   };

   PHS_STATIC_ASSERT_LOG(MSG_MIN == 1, "MSG_MAX is not equal to MSG_COUNT value.");

   static void init();

   /* The arguments should be [string of format "Example 123 {}, {}, ..., {}"] where
   *  each placeholder corresponds to one argument.
   *  Passed arguments should have overloaded operator <<(const std::ostream&, T) for prininting.
   */
   template <typename... Ts>
   static void message(messageLevel lvl, Ts&&... args);
private:
   template <size_t N = 1, typename... Ts>
   static void print_message_queue(std::string format, Ts&&... queue);

   static constexpr size_t           _ArgumentLimit = 16;
   static constexpr size_t           _LevelCount = MSG_MAX;

   static constexpr std::string_view _LevelStr[_LevelCount] =
   {
      "[TRACE]",
      "[DEBUG]",
      "[INFO]",
      "[WARN]",
      "[ERROR]",
      "[FATAL]"
   };

   // ANSI escape sequences for colored output
   static constexpr std::string_view _ANSIColorReset         = "\033[0m";
   static constexpr std::string_view _ANSIColorBlack         = "\033[30m";
   static constexpr std::string_view _ANSIColorRed           = "\033[31m";
   static constexpr std::string_view _ANSIColorGreen         = "\033[32m";
   static constexpr std::string_view _ANSIColorYellow        = "\033[33m";
   static constexpr std::string_view _ANSIColorBlue          = "\033[34m";
   static constexpr std::string_view _ANSIColorMagenta       = "\033[35m";
   static constexpr std::string_view _ANSIColorCyan          = "\033[36m";
   static constexpr std::string_view _ANSIColorWhite         = "\033[37m";
   static constexpr std::string_view _ANSIColorBrightBlack   = "\033[90m";
   static constexpr std::string_view _ANSIColorBrightRed     = "\033[91m";
   static constexpr std::string_view _ANSIColorBrightGreen   = "\033[92m";
   static constexpr std::string_view _ANSIColorBrightYellow  = "\033[93m";
   static constexpr std::string_view _ANSIColorBrightBlue    = "\033[94m";
   static constexpr std::string_view _ANSIColorBrightMagenta = "\033[95m";
   static constexpr std::string_view _ANSIColorBrightCyan    = "\033[96m";
   static constexpr std::string_view _ANSIColorBrightWhite   = "\033[97m";

   static constexpr std::string_view _ANSIColor[_LevelCount] =
   {
        _ANSIColorBrightGreen,
        _ANSIColorBlue,
        _ANSIColorWhite,
        _ANSIColorBrightYellow,
        _ANSIColorYellow,
        _ANSIColorRed,
   };

   static bool _initialized;
};

// Logger API for internal Pheasant development
#define PHS_CORE_LOG_TRACE(...) Log::message(Log::MSG_TRACE, __VA_ARGS__)
#define PHS_CORE_LOG_DEBUG(...) Log::message(Log::MSG_DEBUG, __VA_ARGS__)
#define PHS_CORE_LOG_INFO(...)  Log::message(Log::MSG_INFO,  __VA_ARGS__)
#define PHS_CORE_LOG_WARN(...)  Log::message(Log::MSG_WARN,  __VA_ARGS__)
#define PHS_CORE_LOG_ERROR(...) Log::message(Log::MSG_ERROR, __VA_ARGS__)
#define PHS_CORE_LOG_FATAL(...) Log::message(Log::MSG_FATAL, __VA_ARGS__)

// External logger API for clients
#define PHS_LOG_TRACE(...)      ::Log::message(::Log::MSG_TRACE, __VA_ARGS__)
#define PHS_LOG_DEBUG(...)      ::Log::message(::Log::MSG_DEBUG, __VA_ARGS__)
#define PHS_LOG_INFO(...)       ::Log::message(::Log::MSG_INFO,  __VA_ARGS__)
#define PHS_LOG_WARN(...)       ::Log::message(::Log::MSG_WARN,  __VA_ARGS__)
#define PHS_LOG_ERROR(...)      ::Log::message(::Log::MSG_ERROR, __VA_ARGS__)
#define PHS_LOG_FATAL(...)      ::Log::message(::Log::MSG_FATAL, __VA_ARGS__)

} // namespace Phs

#include "log.inl"
