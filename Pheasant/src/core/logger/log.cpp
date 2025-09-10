#include "precompile.h"
#include "log.h"

namespace Phs 
{

bool Log::_initialized = false;

PHS_INLINE void testMessage(Log::messageLevel lvl)
{
   Log::message(lvl, "Test message");
}

void Log::init() 
{
   std::cout.sync_with_stdio(0);

#ifdef PHS_OS_WINDOWS
   HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);

   if (handle_out == INVALID_HANDLE_VALUE)
   {
      PHS_CORE_LOG_ERROR("Invalid Windows-specific output handle value!");
      return;
   }

   DWORD mode_out;
   if (!GetConsoleMode(handle_out, &mode_out)) 
   {
      PHS_CORE_LOG_ERROR("Failed to get Windows-specific output console mode!");
      return;
   }

   mode_out |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
   mode_out |= DISABLE_NEWLINE_AUTO_RETURN;

   if (!SetConsoleMode(handle_out, mode_out))
   {
      PHS_CORE_LOG_ERROR("Failed to set Windows-specific output console mode!");
      return;
   }
#endif

   _initialized = true;
}

} // namespace Phs
