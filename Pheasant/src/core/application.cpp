#include "precompile.h"
#include "application.h"
#include "log.h"

namespace Phs {

void Application::run()
{
	Log::init();
	PHS_CORE_LOG_TRACE("Welcome to Pheasant!");

	while (true);
}

} // namespace Phs
